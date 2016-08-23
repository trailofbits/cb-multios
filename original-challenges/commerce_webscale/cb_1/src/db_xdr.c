/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "libxdr.h"
#include "db_xdr.h"
int marshal_result_status(result_status *data, unsigned char **_out, size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int unmarshal_result_status(result_status *data, unsigned char **_in, size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int marshal_key(key *data, unsigned char **_out, size_t *_size) {
int _result;
_result = marshal_unsigned_int(&(*data).data.count, _out, _size);
CHECK_RESULT();
if ((*data).data.count > 200) return -1;
{
size_t i;
for (i = 0; i < (*data).data.count; i++) {
_result = marshal_opaque(&(*data).data.data[i], _out, _size);
CHECK_RESULT();
}
}
return 0;
}

int unmarshal_key(key *data, unsigned char **_in, size_t *_size) {
int _result;
_result = unmarshal_unsigned_int(&(*data).data.count, _in, _size);
CHECK_RESULT();
if ((*data).data.count > 200) return -1;
_result = _checked_calloc((void **)&(*data).data.data, (*data).data.count, sizeof((*data).data.data[0]));
{
size_t i;
for (i = 0; i < (*data).data.count; i++) {
_result = unmarshal_opaque(&(*data).data.data[i], _in, _size);
CHECK_RESULT();
}
}
return 0;
}

int marshal_record(record *data, unsigned char **_out, size_t *_size) {
int _result;
_result = marshal_key(&(*data).k, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).data.count, _out, _size);
CHECK_RESULT();
if ((*data).data.count > 1024) return -1;
{
size_t i;
for (i = 0; i < (*data).data.count; i++) {
_result = marshal_opaque(&(*data).data.data[i], _out, _size);
CHECK_RESULT();
}
}
return 0;
}

int unmarshal_record(record *data, unsigned char **_in, size_t *_size) {
int _result;
_result = unmarshal_key(&(*data).k, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).data.count, _in, _size);
CHECK_RESULT();
if ((*data).data.count > 1024) return -1;
_result = _checked_calloc((void **)&(*data).data.data, (*data).data.count, sizeof((*data).data.data[0]));
{
size_t i;
for (i = 0; i < (*data).data.count; i++) {
_result = unmarshal_opaque(&(*data).data.data[i], _in, _size);
CHECK_RESULT();
}
}
return 0;
}

int marshal_result(result *data, unsigned char **_out, size_t *_size) {
int _result;
_result = marshal_result_status(&(*data).status, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).rec.count, _out, _size);
CHECK_RESULT();
if ((*data).rec.count > 1) return -1;
{
size_t i;
for (i = 0; i < (*data).rec.count; i++) {
_result = marshal_record(&(*data).rec.data[i], _out, _size);
CHECK_RESULT();
}
}
return 0;
}

int unmarshal_result(result *data, unsigned char **_in, size_t *_size) {
int _result;
_result = unmarshal_result_status(&(*data).status, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).rec.count, _in, _size);
CHECK_RESULT();
if ((*data).rec.count > 1) return -1;
_result = _checked_calloc((void **)&(*data).rec.data, (*data).rec.count, sizeof((*data).rec.data[0]));
{
size_t i;
for (i = 0; i < (*data).rec.count; i++) {
_result = unmarshal_record(&(*data).rec.data[i], _in, _size);
CHECK_RESULT();
}
}
return 0;
}

