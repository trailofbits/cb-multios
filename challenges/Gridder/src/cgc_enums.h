#pragma once

enum {
    UNUSED = 0,
    USED = 1,
    SET_SUBSIZE = 3,
    SET_SIZE = SET_SUBSIZE * SET_SUBSIZE,
    NUM_CELLS = SET_SIZE * SET_SIZE,
    DIFFICULTY = 25,
    POOL_SIZE = 4096
};
