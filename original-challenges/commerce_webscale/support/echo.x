# example protocol description

const MAXUSERNAME = 32;

enum filekind
{
    TEXT = 0,
    DATA = 1,
    EXEC = 2
};

union filetype switch (filekind kind) {
case TEXT:
    void;
case DATA:
    string creator<MAXNAMELEN>;
};

struct file {
    string filename<MAXNAMELEN>;
    string owner<MAXUSERNAME>;
};
