#include <libcgc.h>
#include <stdlib.h>

void sort_command( char *pszLine )
{
    int idx;
    int sortList[64];
    char szTempBuf[128];

    if ( pszLine == NULL )
    {
        printf( "Empty command.\n" );
        return;
    }

    // BUG:: Overflow possible here
#ifdef PATCHED
    unsigned char itemCount = atoi( pszLine );
#else
    char itemCount = atoi( pszLine );
#endif

    if ( itemCount == 0 )
    {
        printf( "0 items sorted.\n" );
        return;
    }
    else if ( itemCount <= 64 )
        printf( "Enter @d items to sort:\n", itemCount );
    else
    {
        printf( "Maximum of 64 items allowed to sort.\n" );

        return;
    }

    unsigned int itemTotal = (itemCount & 0xFF);

    for ( idx = 0; idx < itemTotal; idx++ )
    {
        getline( szTempBuf, 128 );

        sortList[idx] = atoi( szTempBuf );
    }

    // Begin sorting
    // Naive bubble sort method

    for ( int i = 0; i < (itemTotal-1); i++ )
    {
        int bSwapped = 0;
        for ( int j = 0; j < (itemTotal-i)-1; j++ )
        {
            if ( sortList[j] > sortList[j+1] )
            {
                int temp = sortList[j];
                sortList[j] = sortList[j+1];
                sortList[j+1] = temp;

                bSwapped = 1;
            }
        }

        if ( !bSwapped )
            break;
    }

    printf( "@d items sorted.\n", itemTotal );

    for ( idx = 0; idx < itemTotal; idx++ )
    {
        printf( "@d\n", sortList[idx] );
    }

    // Exit
    return;
}
