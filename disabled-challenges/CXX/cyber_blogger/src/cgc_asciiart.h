#include "cgc_file.h"
#include "cgc_ascii.h"

class AsciiArt : public File, private AsciiInterface
{
private:
    struct AsciiArtHeader
    {
        unsigned int magic;
        unsigned short line_width;
        unsigned short num_lines;
    };

    AsciiArtHeader header;
public:
    AsciiArt(void *_header, void *data, char *_filename);
    virtual ~AsciiArt();

    virtual unsigned int get_magic();
    virtual bool is_ascii(char *_stream);

    static cgc_size_t find_header_size();
    static cgc_size_t find_data_size(void *header);

    void print_asciiart();
};

