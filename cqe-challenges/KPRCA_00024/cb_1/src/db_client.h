/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "db_xdr.h"

int database_init(int fd);
void database_close();
#ifdef DB_CURRENT
result db_lookup (key);
result db_insert (record);
result db_delete (key);
result db_next (key);
result db_prev (key);
#endif /* defined(DB_CURRENT) */
