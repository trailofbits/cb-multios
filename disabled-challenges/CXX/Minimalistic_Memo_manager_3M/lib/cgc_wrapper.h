#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef FILAMENTS
    /* syscalls with wrappers */
    #define cgc_transmit cgc___filaments_transmit
    #define cgc_receive cgc___filaments_receive
    #define cgc_fdwait cgc___filaments_fdwait
    #define cgc_allocate cgc___filaments_allocate
    #define cgc_deallocate cgc___filaments_deallocate
    #define cgc_random cgc___filaments_random
#endif

#endif /* WRAPPER_H */
