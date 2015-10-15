#ifndef SFILE_H_
#define SFILE_H_

enum { BINARY = 0, ASCII = 1 };

// 2 + 2 + 16 + 4 = 24 (header length)
typedef struct sfile {
    char magic[3];
    unsigned char file_type;
    char name[16];
    unsigned int size;

    //char *data;
    char data[];
} SFILE;

SFILE *open_sfile();
void close_sfile(SFILE **psfp);

#endif
