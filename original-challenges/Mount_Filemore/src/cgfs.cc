/*
 * Copyright (c) 2016 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "cgfs.h"
#include <cstdlib.h>
#include <cstring.h>

#include "print.h"

#define FREE_CLUSTER 0x00000000
#define END_OF_FILE 0x0FFFFFF8

#define MAX_IMG_SIZE (1024 * 1024 * 128)
#define MAX_FILE_SIZE (1024 * 1024)

#define OP_READ_FILE 1000
#define OP_WRITE_FILE 2000

CgFsImg::CgFsImg()
{
    is_mounted_ = false;
    cluster_map_ = NULL;
    num_clusters_ = 0;
    cluster_region_ = NULL;
    raw_data_size_ = 0;
    cluster_size_ = 0;
}
CgFsImg::~CgFsImg()
{
    Unmount();
}

bool CgFsImg::IsMounted()
{
    return is_mounted_;
}

bool CgFsImg::Mount(FILE *fs)
{
    if (!fs || is_mounted_)
        return false;

    if (fread((char *)(&hdr_), sizeof(hdr_), fs) != sizeof(hdr_))
        return false;
    if (fread((char *)(&info_sector_), sizeof(info_sector_), fs) != sizeof(info_sector_))
        return false;
    if (hdr_.bytes_per_sector != 512 || hdr_.sectors_per_cluster != 1)
        return false;

    int total_sectors = hdr_.total_sectors_small ? hdr_.total_sectors_small : hdr_.total_sectors_large;
    raw_data_size_ = (total_sectors * hdr_.bytes_per_sector) - sizeof(bhdr) - sizeof(fs_info_sector);
    if (raw_data_size_ > MAX_IMG_SIZE)
        return false;

    num_clusters_ = (hdr_.sectors_per_cgfst * hdr_.bytes_per_sector) / sizeof(unsigned int);

    raw_data_ = new unsigned char[raw_data_size_];
    cluster_map_ = (unsigned int *)(raw_data_ + hdr_.num_reserved_sectors * hdr_.bytes_per_sector - sizeof(bhdr) - sizeof(fs_info_sector));
    cluster_region_ = (unsigned char *)(&cluster_map_[0]) + ((hdr_.sectors_per_cgfst * hdr_.num_cgfst) * hdr_.bytes_per_sector);
    cluster_size_ = hdr_.bytes_per_sector * hdr_.sectors_per_cluster;

    if (fread(raw_data_, raw_data_size_, fs) != raw_data_size_)
        return false;
    is_mounted_ = true;

    char root_name[] = { '/', 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 };
    fs_file *root_entry = new fs_file;
    memset(root_entry->name, 0, sizeof(((fs_file *)0)->name));
    memcpy(root_entry->name, root_name, sizeof(root_name));
    root_entry->attrib = 0x10;
    root_entry->starting_cluster = hdr_.root_cluster_idx;
    root_entry->size = 0;
    root_directory_ = DirectoryTree(root_entry);

    ParseDirectoryTree(&root_directory_, hdr_.root_cluster_idx);


    return true;
}

bool CgFsImg::Unmount()
{
    memset(&hdr_, 0, sizeof(bhdr));
    memset(&info_sector_, 0, sizeof(fs_info_sector));
    if (raw_data_)
        delete[] raw_data_;
    raw_data_ = NULL;
    raw_data_size_ = 0;
    cluster_region_ = NULL;
    cluster_size_ = 0;
    cluster_map_ = NULL;
    num_clusters_ = 0;
    root_directory_.ClearTree(true);
    if (!is_mounted_)
        return false;

    is_mounted_ = false;
    return true;
}

Array<cluster_data> CgFsImg::GetFileClusters(const char *path)
{
    Array<cluster_data> file_clusters;
    fs_file *pfile = root_directory_.FindFile(path);
    if (!pfile)
        return file_clusters;
    else
        return GetFileClusters(pfile->starting_cluster);
}

Array<cluster_data> CgFsImg::GetFileClusters(unsigned int start_cluster)
{
    Array<cluster_data> file_clusters;
    if (!is_mounted_)
        return file_clusters;

    unsigned int cluster_idx = start_cluster;
    while (cluster_idx > 1 && cluster_idx < END_OF_FILE)
    {
        cluster_data file_cluster;
        file_cluster.data = &cluster_region_[(cluster_idx - 2) * cluster_size_];
        file_cluster.cluster_size = cluster_size_;
        file_cluster.cluster_idx = cluster_idx;
        file_clusters.Append(file_cluster);
        cluster_idx = cluster_map_[cluster_idx];
    }

    return file_clusters;
}

void CgFsImg::ListFiles(const char *path, bool recursive)
{
    root_directory_.ListFiles(path, recursive);
}

fs_file *CgFsImg::FindFile(const char *filepath)
{
    return root_directory_.FindFile(filepath);
}

bool CgFsImg::AddFile(const char *dirpath, const char *filename, char *data, unsigned int file_size)
{
    if(!dirpath || !filename || strlen(filename) > sizeof(((fs_file *)0)->name)
            || !file_size || file_size > MAX_FILE_SIZE || FileExists(dirpath, filename))
        return false;

    fs_file *parent_dir = root_directory_.FindFile(dirpath);
    if (!parent_dir || !CgFsFile::IsDirectory(parent_dir))
        return false;

    unsigned int start_cluster = FindUnusedCluster();
    if (!start_cluster)
        return false;

    fs_file new_file;
    new_file.starting_cluster = start_cluster;
    memset(new_file.name, 0x20, sizeof(new_file.name));
    memcpy(new_file.name, filename, strlen(filename));
    new_file.attrib = 0;
    memset(new_file.reserved, 0, sizeof(new_file.reserved));
    new_file.size = file_size;

    AddMetadataEntry(&new_file, parent_dir->starting_cluster);
    cluster_map_[start_cluster] = END_OF_FILE;
    unsigned int allocated_size = file_size > cluster_size_ ? cluster_size_ : file_size;
    if (data)
        memcpy(&cluster_region_[(start_cluster - 2) * cluster_size_], data, allocated_size);
    else
        memset(&cluster_region_[(start_cluster - 2) * cluster_size_], 0, allocated_size);

    while (allocated_size < file_size)
    {
        unsigned int new_cluster_idx = AddCluster(start_cluster);
        unsigned int write_size = file_size - allocated_size > cluster_size_ ? cluster_size_ : file_size - allocated_size;
        if(data)
            memcpy(&cluster_region_[(new_cluster_idx - 2) * cluster_size_], &data[allocated_size], write_size);
        else
            memset(&cluster_region_[(new_cluster_idx - 2) * cluster_size_], 0, write_size);
        allocated_size += write_size;
    }

    RebuildTree();
    return true;
}

bool CgFsImg::AddDirectory(const char *dirpath, const char *dirname)
{
    if(!dirpath || !dirname || strlen(dirname) > sizeof(((fs_file *)0)->name) || FileExists(dirpath, dirname))
        return false;

    fs_file *parent_dir = root_directory_.FindFile(dirpath);
    if (!parent_dir || !CgFsFile::IsDirectory(parent_dir))
        return false;

    unsigned int start_cluster = FindUnusedCluster();
    ClearCluster(start_cluster);
    if (!start_cluster)
        return false;

    fs_file new_file;
    new_file.starting_cluster = start_cluster;
    memset(new_file.name, 0x20, sizeof(new_file.name));
    memcpy(new_file.name, dirname, strlen(dirname));
    new_file.attrib = 0x10;
    memset(new_file.reserved, 0, sizeof(new_file.reserved));
    new_file.size = 0;

    AddMetadataEntry(&new_file, parent_dir->starting_cluster);
    cluster_map_[start_cluster] = END_OF_FILE;

    RebuildTree();
    return true;
}

bool CgFsImg::DeleteFile(const char *path)
{
    fs_file *pfile = root_directory_.FindFile(path);
    if (!pfile || !CgFsFile::IsFile(pfile))
        return false;

    ClearAllClusters(pfile->starting_cluster);
    CgFsFile::DeleteMetadataEntry(pfile);
    RebuildTree();

    return true;
}

bool CgFsImg::DeleteDirectory(const char *path)
{
    DirectoryTree *pdir = root_directory_.FindDirectory(path);
    if (!pdir)
        return false;

    DeleteDirectoryHelper(pdir, pdir == &root_directory_);
    RebuildTree();
    return true;
}

bool CgFsImg::PreviewFile(const char *path, char **pdata, unsigned int *num_bytes)
{
    *num_bytes = 0;
    if (!path || !pdata)
        return false;
    fs_file *found_file = root_directory_.FindFile(path);
    if (!found_file || !CgFsFile::IsFile(found_file))
        return false;

    unsigned int cluster_idx = found_file->starting_cluster;
    if (cluster_idx <= 1 || cluster_idx > END_OF_FILE)
        return false;

    cluster_data file_cluster;
    file_cluster.data = &cluster_region_[(cluster_idx - 2) * cluster_size_];
    file_cluster.cluster_size = cluster_size_;
    file_cluster.cluster_idx = cluster_idx;

    *num_bytes = cluster_size_ < found_file->size  || CgFsFile::IsDirectory(found_file) ? cluster_size_ : found_file->size;
    *pdata = new char[*num_bytes];
    char *data = *pdata;
    memcpy(data, file_cluster.data, *num_bytes);
    return true;
}

bool CgFsImg::ReadFromFile(const char *path, unsigned int offset, unsigned int num_bytes_to_read, char **pdata, unsigned int *num_bytes)
{
    *num_bytes = 0;
    if (!path || !pdata)
        return false;
    fs_file *found_file = root_directory_.FindFile(path);
    if (!found_file || !CgFsFile::IsFile(found_file))
        return false;
    if (offset > found_file->size)
        return false;

    num_bytes_to_read = num_bytes_to_read ? num_bytes_to_read : found_file->size;
    num_bytes_to_read = offset + num_bytes_to_read > found_file->size ? found_file->size - offset : num_bytes_to_read;
    *pdata = new char[num_bytes_to_read];
    char *data = *pdata;
    Array<cluster_data> file_clusters = GetFileClusters(found_file->starting_cluster);
    for (int i = 0; i < file_clusters.length() && *num_bytes < num_bytes_to_read; i++)
    {
        if (offset < i * cluster_size_ || offset >= (i+1) * cluster_size_)
            continue;

        int relative_offset = offset % cluster_size_;
        int num_bytes_left = num_bytes_to_read - *num_bytes;
        int read_size = num_bytes_left <= cluster_size_ ? num_bytes_left : cluster_size_;
        read_size = read_size + relative_offset > cluster_size_ ? read_size - (read_size + relative_offset - cluster_size_) : read_size;
        memcpy(&data[*num_bytes], &file_clusters[i].data[relative_offset], read_size);

        offset = offset - (relative_offset) + cluster_size_;
        *num_bytes += read_size;
    }

    return true;
}

bool CgFsImg::WriteToFile(const char *path, unsigned int offset, unsigned int num_bytes_to_write, char *data, unsigned int *num_bytes)
{
    *num_bytes = 0;
    if (!path || !num_bytes_to_write || !data)
        return false;
    fs_file *found_file = root_directory_.FindFile(path);
    if (!found_file || !CgFsFile::IsFile(found_file))
        return false;
    if (offset > found_file->size)
        return false;

    num_bytes_to_write = offset + num_bytes_to_write > found_file->size ? found_file->size - offset : num_bytes_to_write;
    Array<cluster_data> file_clusters = GetFileClusters(found_file->starting_cluster);
    for (int i = 0; i < file_clusters.length() && *num_bytes < num_bytes_to_write; i++)
    {
        if (offset < i * cluster_size_ || offset >= (i+1) * cluster_size_)
            continue;

        int relative_offset = offset % cluster_size_;
        int num_bytes_left = num_bytes_to_write - *num_bytes;
        int write_size = num_bytes_left <= cluster_size_ ? num_bytes_left : cluster_size_;
        write_size = write_size + relative_offset > cluster_size_ ? write_size - (write_size + relative_offset - cluster_size_) : write_size;

#ifndef PATCHED_1
        if (num_bytes_left < cluster_size_)
            memcpy(&file_clusters[i].data[relative_offset], &data[*num_bytes], num_bytes_left);
        else
            memcpy(&file_clusters[i].data[relative_offset], &data[*num_bytes], write_size);
#else
        memcpy(&file_clusters[i].data[relative_offset], &data[*num_bytes], write_size);
#endif

        offset = offset - (relative_offset) + cluster_size_;
        *num_bytes += write_size;
    }
    return true;
}

bool CgFsImg::UpdateFileSize(const char *path, unsigned int new_size)
{
    if (!path || !new_size)
        return false;
    fs_file *found_file = root_directory_.FindFile(path);
    if (!found_file || !CgFsFile::IsFile(found_file))
        return false;

    unsigned int old_size = found_file->size;
    unsigned int num_old_clusters = (old_size-1) / cluster_size_ + 1;
    unsigned int num_new_clusters = (new_size-1) / cluster_size_ + 1;
    if (old_size == new_size)
        return true;
    else if (old_size < new_size)
    {
        while (num_old_clusters < num_new_clusters)
        {
            if (AddCluster(found_file->starting_cluster))
            {
                ++num_old_clusters;
            }
            else
            {
                found_file->size = num_old_clusters * cluster_size_;
                return false;
            }
        }
        found_file->size = new_size;
        return true;
    }
    else
    {
        while (num_old_clusters > num_new_clusters)
        {
            unsigned int popped_cluster = 0;
            if (PopCluster(found_file->starting_cluster, &popped_cluster))
            {
                --num_old_clusters;
            }
            else
            {
                found_file->size = num_old_clusters * cluster_size_;
                return false;
            }
        }
        found_file->size = new_size;
        return true;
    }
}

void CgFsImg::DebugMetadata()
{
    if (is_mounted_)
    {
        debug_bhdr(hdr_);
        printf(NL NL);
        debug_fs_info(info_sector_);
        printf(NL NL);
        printf("****Cluster Information****" NL);
        printf("Num Clusters = " ESC "d" NL, num_clusters_);
        printf("First 16 bytes of the cluster map:" NL);
        PRINT_ARR_BYTES(cluster_map_, 128);
        printf("First 64 bytes of the cluster region:" NL);
        PRINT_ARR_BYTES(cluster_region_, 64);
        printf("********END METADATA INFO********" NL);
        fflush(stdout);
    }
}

/*********************/
/* Private Functions */
/*********************/
unsigned int CgFsImg::FindUnusedCluster()
{
    for (int i = 3; i < num_clusters_; i++)
    {
        if(cluster_map_[i] == FREE_CLUSTER)
            return i;
    }
    return 0;
}

void CgFsImg::ClearCluster(unsigned int cluster_idx)
{
    if (cluster_idx > 1 && cluster_idx < num_clusters_)
        memset(&cluster_region_[(cluster_idx - 2) * cluster_size_], 0, cluster_size_);
}

unsigned int CgFsImg::AddCluster(unsigned int start_cluster)
{
    unsigned int free_cluster_idx = FindUnusedCluster();
    if (!free_cluster_idx || start_cluster < 2 || start_cluster >= END_OF_FILE)
        return 0;

    unsigned int cluster_idx = start_cluster;
    unsigned int last_cluster_idx = start_cluster;
    while (cluster_idx > 1 && cluster_idx < END_OF_FILE)
    {
        last_cluster_idx = cluster_idx;
        cluster_idx = cluster_map_[cluster_idx];
    }

    cluster_map_[last_cluster_idx] = free_cluster_idx;
    cluster_map_[free_cluster_idx] = END_OF_FILE;
    return free_cluster_idx;
}

bool CgFsImg::PopCluster(unsigned int start_cluster, unsigned int *popped_cluster)
{
    if (start_cluster < 2 || start_cluster >= END_OF_FILE)
        return false;

    unsigned int cluster_idx = start_cluster;
    unsigned int last_cluster_idx = start_cluster;
    unsigned int prev_cluster_idx = start_cluster;
    while (cluster_idx > 1 && cluster_idx < END_OF_FILE)
    {
        prev_cluster_idx = last_cluster_idx;
        last_cluster_idx = cluster_idx;
        cluster_idx = cluster_map_[cluster_idx];
    }

    cluster_map_[prev_cluster_idx] = END_OF_FILE;
    cluster_map_[last_cluster_idx] = FREE_CLUSTER;
    *popped_cluster = last_cluster_idx;
    return true;
}

bool CgFsImg::ClearAllClusters(unsigned int start_cluster)
{
    if (start_cluster < 2 || start_cluster >= END_OF_FILE)
        return false;

    unsigned int cluster_idx = start_cluster;
    unsigned int prev_cluster_idx = start_cluster;
    while (cluster_idx > 1 && cluster_idx < END_OF_FILE)
    {
        prev_cluster_idx = cluster_idx;
        cluster_idx = cluster_map_[cluster_idx];
        cluster_map_[prev_cluster_idx] = FREE_CLUSTER;
    }

    return true;
}

bool CgFsImg::FileExists(const char *path, const char *filename)
{
    if (strlen(filename) > sizeof(((fs_file *)0)->name))
        return false;

    char *file_path = new char[strlen(path) + strlen(filename) + 2];
    memset(file_path, 0, strlen(path) + strlen(filename) + 2);
    unsigned int file_path_len = strlen(path);
    memcpy(file_path, path, strlen(path));
    if(file_path[strlen(path) - 1] != '/')
        file_path[file_path_len++] = '/';
    memcpy(&file_path[file_path_len], filename, strlen(filename));
    fs_file *found_file = root_directory_.FindFile(file_path);
    delete[] file_path;

    return found_file;
}

void CgFsImg::DeleteDirectoryHelper(DirectoryTree *dirnode, bool is_root)
{
    if (!dirnode)
        return;

    for (int i = 0; i < dirnode->subdirectories().length(); i++)
    {
        DeleteDirectoryHelper(&dirnode->subdirectories()[i], false);
    }
    for (int i = 0; i < dirnode->file_list().length(); i++)
    {
        fs_file *pfile = dirnode->file_list()[i];
        ClearAllClusters(pfile->starting_cluster);
        CgFsFile::DeleteMetadataEntry(pfile);
    }

    if (!is_root)
    {
        fs_file *pdir = dirnode->directory_entry();
        ClearAllClusters(pdir->starting_cluster);
        CgFsFile::DeleteMetadataEntry(pdir);
    }
}

void CgFsImg::AddMetadataEntry(fs_file *new_entry, unsigned int directory_cluster_idx)
{
    Array<cluster_data> directory_clusters = GetFileClusters(directory_cluster_idx);
    for (int i = 0; i < directory_clusters.length(); i++)
    {
        for (int j = 0; j+sizeof(fs_file) <= directory_clusters[i].cluster_size; j += sizeof(fs_file))
        {
            fs_file *pfile_info = (fs_file *)&directory_clusters[i].data[j];
            if (CgFsFile::FreeEntry(pfile_info))
            {
                memcpy(pfile_info, new_entry, sizeof(fs_file));
                return;
            }
        }
    }

    unsigned int new_cluster_idx = AddCluster(directory_cluster_idx);
    ClearCluster(new_cluster_idx);
    fs_file *pfile_info = (fs_file *)&cluster_region_[(new_cluster_idx - 2) * cluster_size_];
    memcpy(pfile_info, new_entry, sizeof(fs_file));
}

void CgFsImg::ParseDirectoryTree(DirectoryTree *rootdir)
{
    ParseDirectoryTree(rootdir, rootdir->directory_entry()->starting_cluster);
}

void CgFsImg::ParseDirectoryTree(DirectoryTree *directory, unsigned int directory_cluster_idx)
{
    Array<cluster_data> directory_clusters = GetFileClusters(directory_cluster_idx);
    for (int i = 0; i < directory_clusters.length(); i++)
    {
        for (int j = 0; j+sizeof(fs_file) <= directory_clusters[i].cluster_size; j += sizeof(fs_file))
        {
            fs_file *pfile_info = (fs_file *)&directory_clusters[i].data[j];
            if (!CgFsFile::SkipEntry(pfile_info) && !CgFsFile::IsDotEntry(pfile_info))
                directory->AddEntry(pfile_info);
        }
    }

    Array<DirectoryTree> subdirectories = directory->subdirectories();
    for (int i = 0; i < subdirectories.length(); i++)
        ParseDirectoryTree(&subdirectories[i], subdirectories[i].directory_entry()->starting_cluster);
}

void CgFsImg::RebuildTree()
{
    root_directory_.ClearTree(false);
    ParseDirectoryTree(&root_directory_);
}
