#ifndef ASCII_H
#define ASCII_H

class AsciiInterface
{
public:
    AsciiInterface() {}
    ~AsciiInterface() {}
    virtual bool is_ascii(char *_stream) = 0;
};

#endif
