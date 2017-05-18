#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define ERROR_CODE(_x) (-1<<_x)
#define BAD_CHARACTER ERROR_CODE(1)
#define BAD_RE ERROR_CODE(2)
#define BAD_ESCAPE_CHAR ERROR_CODE(3)
#define MAX_RE_SIZE ERROR_CODE(4)
#define RE_TOO_LONG ERROR_CODE(5)
#define BUF_OVERFLOW ERROR_CODE(6)

#define CHAR_OFFSET 128

#define OP_OFFSET(_c) (_c + CHAR_OFFSET)

#define PUSH(_list, _item)   \
    do {                     \
        *_list++ = _item;    \
    } while(0);

#define POP(_list, _item)    \
    do {                     \
        _item = *--_list;    \
        *_list = 0;       \
    } while(0);

enum { TRUE = 1, FALSE = 0 };
enum { EPSILON = 128, LPAREN = OP_OFFSET('('), RPAREN = OP_OFFSET(')'), CONCAT = OP_OFFSET('&'),
        UNION = OP_OFFSET('|'), STAR = OP_OFFSET('*'), QMARK = OP_OFFSET('?'), PLUS = OP_OFFSET('+'),
        SKIP = OP_OFFSET('\\')};

#endif
