/* AUTOMATICALLY GENERATED - DO NOT EDIT! */

#include <stdlib.h>
#include "libxdr.h"
/* Begin constants */
#define EXISTS 1
#define SUCCESS 0
#define MISSING 2
/* End constants */

typedef long result_status;

typedef struct key key;

typedef struct record record;

typedef struct result result;

;

struct key {
    struct {
        unsigned long count;
        opaque *data;
    } data;
};

struct record {
    key k;
    struct {
        unsigned long count;
        opaque *data;
    } data;
};

struct result {
    result_status status;
    struct {
        unsigned long count;
        record *data;
    } rec;
};

int marshal_result_status(result_status *data, unsigned char **_out, size_t *_size);
int unmarshal_result_status(result_status *data, unsigned char **_in, size_t *_size);
int marshal_key(key *data, unsigned char **_out, size_t *_size);
int unmarshal_key(key *data, unsigned char **_in, size_t *_size);
int marshal_record(record *data, unsigned char **_out, size_t *_size);
int unmarshal_record(record *data, unsigned char **_in, size_t *_size);
int marshal_result(result *data, unsigned char **_out, size_t *_size);
int unmarshal_result(result *data, unsigned char **_in, size_t *_size);
