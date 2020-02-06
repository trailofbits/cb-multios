#define htobe32(x) (((((x) >> 24) & 0xff) <<  0) | \
                    ((((x) >> 16) & 0xff) <<  8) | \
                    ((((x) >>  8) & 0xff) << 16) | \
                    ((((x) >>  0) & 0xff) << 24))

#define htobe16(x) (((((x) >>  8) & 0xff) <<  0) | \
                    ((((x) >>  0) & 0xff) <<  8))

#define be32toh htobe32
#define be16toh htobe16
