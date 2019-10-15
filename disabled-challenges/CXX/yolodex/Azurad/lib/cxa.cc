#include "cgc_cstdlib.h"

extern "C"
{
    void __cxa_pure_virtual()
    {
        cgc__terminate(1);
    }
}
