#include <libpov.h>

int main(void) {
    do {
        //*** negotiating a type 1 POV
        unsigned int povType = 1;
        transmit_all(3, &povType, sizeof(povType));
        unsigned int ipmask = 0xFEFEFEFE;
        unsigned int regmask = 0xFEFEFEFE;
        unsigned int regnum = 6;
        unsigned int type1vals[2];
        if (transmit_all(3, (void *) &ipmask, sizeof(unsigned int)) != 0) {
            _terminate(1);
        }
        if (transmit_all(3, (void *) &regmask, sizeof(unsigned int)) != 0) {
            _terminate(2);
        }
        if (transmit_all(3, (void *) &regnum, sizeof(unsigned int)) != 0) {
            _terminate(3);
        }
        if (length_read(3, (unsigned char *)type1vals, sizeof(type1vals)) != sizeof(type1vals)) {
            _terminate(4);
        }
        type1vals[0] = type1vals[0] | 0x01010101;
        type1vals[1] = type1vals[1] | 0x01010101;
        putenv("TYPE1_IP", (unsigned char*)&type1vals[0], sizeof(unsigned int));
        putenv("TYPE1_REG", (unsigned char*)&type1vals[1], sizeof(unsigned int));
    } while(0);

    do {
        //**** delimited read
        static unsigned char read_00000_delim[] = 
            "\x0a";
        unsigned char *read_00000 = NULL;
        unsigned int read_00000_len = 0;
        int read_00000_res = delimited_read(0, &read_00000, &read_00000_len, read_00000_delim, 1);
        free(read_00000);
    } while (0);
    
    do {
        //**** delimited read
        static unsigned char read_00001_delim[] = 
            "\x0a";
        unsigned char *read_00001 = NULL;
        unsigned int read_00001_len = 0;
        int read_00001_res = delimited_read(0, &read_00001, &read_00001_len, read_00001_delim, 1);
        free(read_00001);
    } while (0);
    
    do {
        //**** delimited read
        static unsigned char read_00002_delim[] = 
            "\x0a";
        unsigned char *read_00002 = NULL;
        unsigned int read_00002_len = 0;
        int read_00002_res = delimited_read(0, &read_00002, &read_00002_len, read_00002_delim, 1);
        free(read_00002);
    } while (0);
    
    do {
        //**** length read
        unsigned char *read_00003 = (unsigned char*)malloc(37);
        unsigned int read_00003_len = 37;
        int read_00003_res = length_read(0, read_00003, 37);
        free(read_00003);
    } while (0);
    
    do {
        //*** writing data
        static unsigned char write_00000_00000[] = 
            "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
            "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
            "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
            "\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41\x41"
            "\x42\x42\x42\x42\x01\x00\x00\x00\x01\x00\x00\x00\x41\x41\x41\x41";
        static unsigned int write_00000_00000_len = 80;
        static unsigned char write_00000_00002[] = 
            "\x43\x43\x43\x43";
        static unsigned int write_00000_00002_len = 4;
        static unsigned char write_00000_00004[] = 
            "\x0a";
        static unsigned int write_00000_00004_len = 1;
        unsigned char *write_00000 = NULL;
        unsigned int write_00000_len = 0;
        write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00000, write_00000_00000_len);
        write_00000 = append_var("TYPE1_REG", write_00000, &write_00000_len);
        write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00002, write_00000_00002_len);
        write_00000 = append_var("TYPE1_IP", write_00000, &write_00000_len);
        write_00000 = append_buf(write_00000, &write_00000_len, write_00000_00004, write_00000_00004_len);
        if (write_00000_len > 0) {
            transmit_all(1, write_00000, write_00000_len);
        }
        free(write_00000);
    } while (0);
}
