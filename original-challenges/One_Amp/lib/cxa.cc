#include <cstdlib.h>

extern "C"
{
    void __cxa_pure_virtual()
    {
        _terminate(1);
    }
}
