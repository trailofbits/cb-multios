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

#ifndef CgFs_H_
#define CgFs_H_

#include <cstdio.h>
#include "bhdr.h"
#include "fs_info_sector.h"
#include "cluster.h"
#include "directory_tree.h"

class CgFsImg
{
  public:
    CgFsImg();
    ~CgFsImg();

    unsigned int cgfst_id();
    unsigned int end_of_cluster_marker();

    bool IsMounted();
    bool Mount(FILE *img);
    bool Unmount();

    Array<cluster_data> GetFileClusters(const char *path);
    Array<cluster_data> GetFileClusters(unsigned int start_cluster);
    void ListFiles(const char *path, bool recursive);

    fs_file *FindFile(const char *filepath);
    bool AddFile(const char *path, const char *filename, char *data, unsigned int file_size);
    bool AddDirectory(const char *path, const char *dirname);
    bool DeleteFile(const char *path);
    bool DeleteDirectory(const char *path);

    bool PreviewFile(const char *path, char **pdata, unsigned int *num_bytes);
    bool ReadFromFile(const char *path, unsigned int offset, unsigned int num_bytes_to_read, char **pdata, unsigned int *num_bytes_read);
    bool WriteToFile(const char *path, unsigned int offset, unsigned int num_bytes_to_write, char *data, unsigned int *num_bytes_written);
    bool UpdateFileSize(const char *path, unsigned int new_size);

    void DebugMetadata();
  private:
    bool is_mounted_;
    bhdr hdr_;
    fs_info_sector info_sector_;

    unsigned int *cluster_map_;
    unsigned int num_clusters_;

    unsigned char *cluster_region_;
    unsigned int cluster_size_;
    unsigned char *raw_data_;
    unsigned int raw_data_size_;
    DirectoryTree root_directory_;

    unsigned int FindUnusedCluster();
    void ClearCluster(unsigned int cluster_idx);
    unsigned int AddCluster(unsigned int start_cluster);
    bool PopCluster(unsigned int start_cluster, unsigned int *popped_cluster);
    bool ClearAllClusters(unsigned int start_cluster);

    bool FileExists(const char *dirpath, const char *filename);
    void DeleteDirectoryHelper(DirectoryTree *dirnode, bool is_root);
    bool FileReadWrite(const char *path, unsigned int offset, unsigned int num_bytes_to_rw, char *data, unsigned int *num_bytes, unsigned int operation);

    void AddMetadataEntry(fs_file *new_entry, unsigned int directory_cluster_idx);
    void ParseDirectoryTree(DirectoryTree *directory);
    void ParseDirectoryTree(DirectoryTree *directory, unsigned int directory_cluster_idx);
    void RebuildTree();
};

#endif
