/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "cgc_libc.h"
#include "cgc_stdint.h"
#include "cgc_malloc.h"
#include "cgc_fs.h"

#define DIRSEP "#"
#define DIRSEPCHR '#'
#define READMESTR "This is a sample file! Feel free to add your own!"

#define CHECKINIT() if (!root) cgc_init_fs();


static dirtree_t *root;

static void cgc_freedir(void *data);

static void cgc_freefile(void *data);

static bool cgc_get_file(void *fdata, void *data); 

static struct node *cgc_get_dir(struct node *cur, void *data);

char *cgc_ls_dir(char *path) {
    cgc_size_t len = 0;
    cgc_size_t idx;
    int i;
    char *dirlist;
    file_t *file;
    struct list *files;
    struct node *dirnode;
    dirtree_t *dir;
    struct node *head, *cur;
    cgc_size_t plen = cgc_strlen(path);

    debug("listing fs path @b\n", path);
    CHECKINIT();

    if (!plen) {
        debug("Path too short.\n");
        return NULL;
    } else if (plen == 1 && *path == DIRSEPCHR) {
        dir = root;
    } else {
        dirnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, path);
        if (!dirnode) {
            debug("Failed to find dir.\n");
            return NULL;
        }

        dir = (dirtree_t*)(dirnode->data);
    }

    files = &(dir->files);

    head = cgc_list_head_node(files);

    for (i=0, cur=head; i < cgc_list_length(files); i++) {
        len += cgc_strlen(((file_t*)cur->data)->name)+1;
        cur = cur->next;
    }

    len++;
    dirlist = cgc_calloc(len);

    if (!dirlist) {
        debug("Failed to allocate dirlist.\n");
        return NULL;
    }

    for (i=0, idx = 0, cur = head; i < cgc_list_length(files); i++) {
        file = ((file_t*)cur->data);
        cgc_strcpy(dirlist+idx, file->name);
        idx += cgc_strlen(file->name);
        *(dirlist+idx++) = ':';
        cur = cur->next;
    }

    *(dirlist+idx-1) = '\0';
    return dirlist;
}

int cgc_add_dir(char *path) {
    char *fn = NULL;
    char *tmp;
    char *parent;
    dirtree_t *nd;
    dirtree_t *dir;
    struct node *dirnode;

    debug("add dir @b\n", path);

    CHECKINIT();

    if (cgc_strlen(path) <= 1) {
        debug("Path is too short.\n");
        return 3;
    }

    if (cgc_strlen(path) > MAX_FILENAME_SIZE) {
        debug("Path is too long.\n");
        return 4;
    }

    dirnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, path);

    if (dirnode) {
        debug("Path already exists.\n");
        return 1;
    }

    parent = cgc_calloc(cgc_strlen(path)+1);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return 2;
    }

    tmp = cgc_strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                cgc_strcat(parent, DIRSEP);
            else
                cgc_strcat(parent, fn);
        }
        fn = tmp;
        tmp = cgc_strtok(NULL, DIRSEPCHR);
    }

    if (cgc_strlen(fn) < 1) {
        debug("Filename too short.\n");
        return 2;
    }

    if (cgc_strlen(parent) > 1) {
        dirnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, path);
        debug("path: @b\n",path);
        if (!dirnode) {
            debug("Failed to find directory.\n");
            return 3;
        }
        dir = (dirtree_t*)(dirnode->data);
    } else {
        dir = root;
    }

    nd = cgc_calloc(sizeof(dirtree_t));

    if (!nd) {
        debug("Failed to allocate directory.\n");
        return 1;
    }

    cgc_strcpy(nd->name, fn);

    cgc_list_init(&nd->directories, cgc_freedir);
    cgc_list_init(&nd->files, cgc_freefile);

    cgc_list_insert_at_end(&dir->directories, nd); 

    return 0;
}

int cgc_rm_dir(char *path) {
    char *fn = NULL;
    char *tmp = NULL;
    char *parent;
    cgc_size_t len;
    int i;
    struct list *dir;
    struct node *parentnode;
    struct node *cur;

    debug("rm dir @b\n", path);
    CHECKINIT();

    if(!path) {
        debug("Passed null path.\n");
        return 1;
    }

    len = cgc_strlen(path);

    if (len > MAX_FILENAME_SIZE) {
        debug("Path was too long.\n");
        return 2;
    }

    if (len <= 1) {
        debug("Path was too short.\n");
        return 7;
    }

    parent = cgc_calloc(len+1);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return 3;
    }

    tmp = cgc_strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                cgc_strcat(parent, DIRSEP);
            else
                cgc_strcat(parent, fn);
        }
        fn = tmp;
        tmp = cgc_strtok(NULL, DIRSEPCHR);
    }

    if (cgc_strlen(parent) == 1 && *parent == DIRSEPCHR) {
        dir = &root->directories;
    } else {
        parentnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, parent);

        if (!parentnode) {
            debug("Unable to find parent directory @b\n", parent);
            return 5;
        }

        dir = &((dirtree_t*)(parentnode->data))->directories;
    }

    if (!dir) {
        debug("Failed to get directory list.\n");
        return 6;
    }

    cur = cgc_list_head_node(dir);
    for (i=0; i < cgc_list_length(dir); i++) {
        if (cgc_streq(fn,((dirtree_t*)(cur->data))->name)) {
            cgc_list_remove_node(dir, cur);
            cgc_list_destroy_node(dir, &cur);
            return 0;
        }
        cur = cur->next;
    }
    
    debug("Failed to find directory to delete.\n");
    return 1;
}

int cgc_add_file(char *path, char *data) {
    file_t *nf;
    dirtree_t *dir;
    struct node *dirnode;
    char *fn = NULL;
    char *tmp;
    int i = 0, count = 0;
    cgc_size_t len;

    debug("add file @b\n", path);
    CHECKINIT();

    dirnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, path);

    if (!dirnode) {

        while (*(path+i) != '\0') {
            count += *(path+i++) == DIRSEPCHR;
        }

        if (*path != DIRSEPCHR && count != 1) {
            debug("Failed to parse file path.\n");
            return 1;
        } else {
            dir = root;
        }

    } else {
        dir = (dirtree_t *)dirnode->data;
    }

    tmp = cgc_strtok(path, DIRSEPCHR);

    while (tmp) {
        fn = tmp;
        tmp = cgc_strtok(NULL, DIRSEPCHR);
    }

    len = cgc_strlen(fn);

    if (len < 1) {
        debug("Filename too short.\n");
        return 2;
    }

    if (len > MAX_FILENAME_SIZE) {
        debug("Filename too long.\n");
        return 3;
    }

    if (cgc_strlen(data)+1 > MAX_FILE_SIZE) {
        debug("File data too long.\n");
        return 4;
    }

    if (!cgc_list_find_node_with_data(&dir->files, cgc_get_file, fn)) {
        nf  = cgc_calloc(sizeof(file_t));

        if (!nf) {
            debug("Failed to allocate new file.\n");
            return 7;
        }

        cgc_strcpy(nf->data, data);
        cgc_strcpy(nf->name, fn);

        cgc_list_insert_at_end(&dir->files, nf); 

        return 0;
    } else {
        debug("File already exists.\n");
        return 1;
    }
}

int cgc_rm_file(char *path) {
    char *fn = NULL;
    char *tmp = NULL;
    char *parent;
    cgc_size_t len;
    int i;
    struct list *files;
    struct node *parentnode;
    struct node *cur;

    debug("rm file @b\n", path);
    CHECKINIT();

    if(!path) {
        debug("Invalid arguments.\n");
        return 1;
    }

    len = cgc_strlen(path);

    if (len > MAX_FILENAME_SIZE) {
        debug("Path was too long.\n");
        return 2;
    }

    if (len <= 1) {
        debug("Path was too short.\n");
        return 7;
    }

    parent = cgc_calloc(len+1);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return 3;
    }

    tmp = cgc_strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                cgc_strcat(parent, DIRSEP);
            else
                cgc_strcat(parent, fn);
        }
        fn = tmp;
        tmp = cgc_strtok(NULL, DIRSEPCHR);
    }

    if (cgc_strlen(parent) == 1 && *parent == DIRSEPCHR) {
        files = &root->files;
    } else {
        parentnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, parent);

        if (!parentnode) {
            debug("Unable to find parent directory @b\n", parent);
            return 5;
        }

        files = &((dirtree_t*)(parentnode->data))->files;
    }

    if (!files) {
        debug("Could not enumerate directory.\n");
        return 7;
    }

    cur = cgc_list_head_node(files);
    for (i=0; i < cgc_list_length(files); i++) {
        debug("found @b\n",((file_t*)(cur->data))->name);
        if (cgc_streq(fn,((file_t*)(cur->data))->name)) {
            cgc_list_remove_node(files, cur);
            cgc_list_destroy_node(files, &cur);
            return 0;
        }
        cur = cur->next;
    }
    
    debug("Failed to find file to delete. @b @b\n", parent, fn);
    return 1;
}

char *cgc_readfile(char *path) {
    dirtree_t *dir;
    struct node *dirnode, *filenode;
    char *fn = NULL;
    char *tmp;
    char *parent;
    cgc_size_t plen;
    debug("read file @b\n", path);

    CHECKINIT();

    plen = cgc_strlen(path);

    if (plen > MAX_FILENAME_SIZE) {
        debug("File path too long.\n", path);
        return NULL;
    }

    if (plen <= 1) {
        debug("File path too short.\n");
        return NULL;
    }

    parent = cgc_calloc(MAX_FILENAME_SIZE);

    if (!parent) {
        debug("Failed to allocate string.\n");
        return NULL;
    }

    tmp = cgc_strtok(path, DIRSEPCHR);
    while (tmp) {
        if (fn) {
            if (!*fn)
                cgc_strcat(parent, DIRSEP);
            else
                cgc_strcat(parent, fn);
        }
        fn = tmp;
        tmp = cgc_strtok(NULL, DIRSEPCHR);
    }


    if (cgc_strlen(fn) < 1) {
        debug("Filename too short.\n");
        return NULL;
    }

    debug("parent: @b\n", parent);
    if (cgc_strlen(parent) == 1 && *parent == DIRSEPCHR) {
        filenode = cgc_list_find_node_with_data(&root->files, cgc_get_file, fn);
    } else {
        dirnode = cgc_list_find_node_with_data_recurse(&root->directories, &cgc_get_dir, parent);

        if (!dirnode) {
            debug("Could not find file directory: @b.\n", parent);
            return NULL;
        }

        dir = (dirtree_t *)dirnode->data;

        filenode = cgc_list_find_node_with_data(&dir->files, cgc_get_file, fn);
    }

    if (!filenode) {
        debug ("Could not find file.\n");
        return NULL;
    }

    return ((file_t*)filenode->data)->data;
}

void cgc_init_fs() {
    char readmepath[] = DIRSEP"README";
    debug("init_fs...\n");

    if (root)
        cgc__terminate(8);

    root = cgc_calloc(sizeof(dirtree_t));

    if (!root)
        cgc__terminate(9);

    cgc_strcpy(root->name, DIRSEP);

    cgc_list_init(&root->directories, cgc_freedir);
    cgc_list_init(&root->files, cgc_freefile);

    if (cgc_add_file(readmepath, READMESTR))
        cgc__terminate(6);
}

static void cgc_freedir(void *data) {
    dirtree_t *dir = (dirtree_t*)data;

    debug("freeing dir @b\n", dir->name);

    cgc_list_destroy(&dir->directories);
    cgc_list_destroy(&dir->files);
    cgc_free(dir);
}

static void cgc_freefile(void *data) {
    file_t *file = (file_t *)data;
    debug("freeing file @b\n", file->name);

    cgc_free(file);
}

static bool cgc_get_file(void *fdata, void *data) {
    file_t *f = (file_t *)fdata;

    if (cgc_streq(f->name, (char *)data))
        return true;
    return false;
}

static struct node *cgc_get_dir(struct node *cur, void *data) {
    char *path = (char *)data;
    struct node *res;
    dirtree_t *d = (dirtree_t *)cur->data;
    char *tmp = d->name;

    if (*path++ != DIRSEPCHR)
        return NULL;

    while (*path != '\0' && *path != DIRSEPCHR) {
        if (*tmp++ != *path++)
            return NULL;
    }

    if (*tmp == '\0' && *path == '\0')
        return cur;

    if (*path == '\0')
        return NULL;

    if ((res = cgc_list_find_node_with_data_recurse(&d->directories, &cgc_get_dir, path))) {
        return res;
    } else {
        path++;
        while (*path != '\0') {
            if (*path == DIRSEPCHR)
                return NULL;
            path++;
        }
        return cur;
    }
}
