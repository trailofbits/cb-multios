#ifndef COMMON_H_
#define COMMON_H_

enum {
    SUCCESS,
    FAILURE
};

#define INVALID ((unsigned int)-1)
#define ROUNDUP(x, y) (((x) + (y) - 1) & ~((y) - 1))

#endif
