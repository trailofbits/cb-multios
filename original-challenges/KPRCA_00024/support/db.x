enum result_status {
    SUCCESS = 0,
    EXISTS = 1,
    MISSING = 2
};

struct key {
    opaque data<200>;
};

struct record {
    key k;
    opaque data<1024>;
};

struct result {
    result_status status;
    record * rec;
};

program database {
    version DB_CURRENT {
        result db_lookup(key) = 1;
        result db_insert(record) = 2;
        result db_delete(key) = 3;
        result db_next(key) = 4;
        result db_prev(key) = 5;
    } = 1;
} = 232323;
