#ifndef ALPHABET_H_
#define ALPHABET_H_

#define ALPHABET_SIZE 26
#define ALPHABET_START 'A'

typedef struct {
    unsigned int freq[ALPHABET_SIZE];
} freqtab_t;

void cgc_ftab_init(freqtab_t *ftab, const char *word);
void cgc_ftab_init1(freqtab_t *ftab);
void cgc_ftab_add(freqtab_t *ftab, const char *word);

#endif /* !ALPHABET_H_ */
