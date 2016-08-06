#ifndef FILETYPE_H_
#define FILETYPE_H_

extern "C" {
#include<string.h>
};

enum ftype {BADFILE=0, ASCIIART, PICTURE, PJEG, ICON };

struct filetype {
    const ftype type;
    const char *extension;
    unsigned int magic;
};

const filetype *get_filetype_m(unsigned int magic);
const filetype *get_filetype_e(char *extension);

#endif
