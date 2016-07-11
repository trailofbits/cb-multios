#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef FILAMENTS
    /* syscalls with wrappers */
    #define transmit __filaments_transmit
    #define receive __filaments_receive
    #define fdwait __filaments_fdwait
    #define allocate __filaments_allocate
    #define deallocate __filaments_deallocate
    #define random __filaments_random
#endif

#endif /* WRAPPER_H */
