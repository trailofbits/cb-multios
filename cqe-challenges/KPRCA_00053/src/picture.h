#include "file.h"

class Picture : public File
{
private:
    struct PictureHeader
    {
        unsigned int magic;
        unsigned int data_size;
    };

    PictureHeader header;
public:
    Picture(void *header, void *data, char *_filename);
    virtual ~Picture();

    virtual unsigned int get_magic();

    static size_t find_header_size();
    static size_t find_data_size(void *header);

    void print_picture();
};
