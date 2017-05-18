#ifndef STDINT_H_
#define STDINT_H_

/* Minimum of signed integral types.  */
#define INT8_MIN       (-128)
#define INT16_MIN      (-32767-1)
#define INT32_MIN      (-2147483647-1)
#define INT64_MIN      (-(9223372036854775807LL)-1)
#define INT_MIN        INT32_MIN
#define LONG_MIN       INT32_MIN

/* Maximum of signed integral types.  */
#define INT8_MAX       (127)
#define INT16_MAX      (32767)
#define INT32_MAX      (2147483647)
#define INT64_MAX      (9223372036854775807LL)
#define INT_MAX        INT32_MAX
#define LONG_MAX       INT32_MAX

/* Maximum of unsigned integral types.  */
#define UINT8_MAX      (255)
#define UINT16_MAX     (65535)
#define UINT32_MAX     (4294967295U)
#define UINT64_MAX     (18446744073709551615ULL)
#define UINT_MAX       UINT32_MAX
#define ULONG_MAX      UINT32_MAX

#endif
