/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "cgc_db_xdr.h"

int cgc_database_init(int fdr, int fdw);
void cgc_database_close();
#ifdef DB_CURRENT
result cgc_db_lookup (key);
result cgc_db_insert (record);
result cgc_db_delete (key);
result cgc_db_next (key);
result cgc_db_prev (key);
#endif /* defined(DB_CURRENT) */
