
#define IS_DIGIT     1
#define IS_UPPER     2
#define IS_LOWER     4
#define IS_SPACE     8
#define IS_XDIGIT    16
#define IS_CTRL      32
#define IS_BLANK     64

#define IS_ALPHA     (IS_LOWER | IS_UPPER)
#define IS_ALNUM     (IS_ALPHA | IS_DIGIT)

static unsigned char type_flags[256] = {
     0, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,
     IS_CTRL, IS_SPACE | IS_BLANK, IS_SPACE, IS_SPACE, IS_SPACE, IS_SPACE, IS_CTRL, IS_CTRL,

     IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,
     IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,

     IS_SPACE | IS_BLANK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

     IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT,
     IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, 0, 0, 0, 0, 0, 0,

     0, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER,
     IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER,

     IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER,
     IS_UPPER, IS_UPPER, IS_UPPER, 0, 0, 0, 0, 0,

     0, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER,
     IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER,

     IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER,
     IS_LOWER, IS_LOWER, IS_LOWER, 0, 0, 0, 0, 0,
};

int isalnum(int c) {
   return (type_flags[c & 0xff] & IS_ALNUM) != 0;
}

int isalpha(int c) {
   return (type_flags[c & 0xff] & IS_ALPHA) != 0;
}

int iscntrl(int c) {
   return (type_flags[c & 0xff] & IS_CTRL) != 0;
}

int isdigit(int c) {
   return (type_flags[c & 0xff] & IS_DIGIT) != 0;
}

int isgraph(int c) {
   return c > ' ' && c <= '~';
}

int islower(int c) {
   return (type_flags[c & 0xff] & IS_LOWER) != 0;
}

int isprint(int c) {
   return c >= ' ' && c <= '~';
}

int ispunct(int c) {
   return isprint(c) && (type_flags[c & 0xff] & (IS_SPACE | IS_ALNUM)) == 0;
}

int isspace(int c) {
   return (type_flags[c & 0xff] & IS_SPACE) != 0;
}

int isupper(int c) {
   return (type_flags[c & 0xff] & IS_UPPER) != 0;
}

int isxdigit(int c) {
   return (type_flags[c & 0xff] & IS_XDIGIT) != 0;
}




