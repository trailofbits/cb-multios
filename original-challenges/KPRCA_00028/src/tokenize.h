#ifndef __TOKENIZE_H_
#define __TOKENIZE_H_

#include "list.h"

DEF_LIST(tok, char *);

tok_list *tokenize(char *expr);

#endif /* __TOKENIZE_H_ */
