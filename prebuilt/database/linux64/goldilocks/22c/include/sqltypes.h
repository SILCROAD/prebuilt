/********************************************************
 * ODBC Specification
 *
 * Copyright (c) Microsoft Corporation
 *
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ""Software""), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __SQLTYPES_H
#define __SQLTYPES_H 1

/* if ODBCVER is not defined, default to ODBC 3.80 */
#ifndef ODBCVER
#define ODBCVER    0x0380
#endif  /* ODBCVER */



#include <goldilocks.h>

#ifdef __cplusplus
extern "C" {  /* Assume C declarations for C++   */
#endif  /* __cplusplus */

/* environment specific definitions */
#ifndef EXPORT
#define EXPORT
#endif




#define SQL_API


/* API declaration data types */
typedef unsigned char                           SQLCHAR;
#if (ODBCVER >= 0x0300)
typedef signed char                             SQLSCHAR;
typedef unsigned char                           SQLDATE;
typedef unsigned char                           SQLDECIMAL;
typedef double                                  SQLDOUBLE;
typedef double                                  SQLFLOAT;
#endif
typedef int                                     SQLINTEGER;
typedef unsigned int                            SQLUINTEGER;

#if (SIZEOF_LONG_INT == 8)
#ifdef USE_4BYTE_SQLLEN
#define SQLLEN                                  SQLINTEGER
#define SQLULEN                                 SQLUINTEGER
#define SQLSETPOSIROW                           SQLUSMALLINT
#else
typedef long                                    SQLLEN;
typedef unsigned long                           SQLULEN;
typedef unsigned long                           SQLSETPOSIROW;
#endif
#else
#define SQLLEN                                  SQLINTEGER
#define SQLULEN                                 SQLUINTEGER
#define SQLSETPOSIROW                           SQLUSMALLINT
#endif

//For Backward compatibility
typedef SQLULEN                                 SQLROWCOUNT;
typedef SQLULEN                                 SQLROWSETSIZE;
typedef SQLULEN                                 SQLTRANSID;
typedef SQLLEN                                  SQLROWOFFSET;

#if (ODBCVER >= 0x0300)
typedef unsigned char                           SQLNUMERIC;
#endif
typedef void *                                  SQLPOINTER;
#if (ODBCVER >= 0x0300)
typedef float                                   SQLREAL;
#endif
typedef short                                   SQLSMALLINT;
typedef unsigned short                          SQLUSMALLINT;
#if (ODBCVER >= 0x0300)
typedef unsigned char                           SQLTIME;
typedef unsigned char                           SQLTIMESTAMP;
typedef unsigned char                           SQLVARCHAR;
#endif
#if (ODBCVER >= 0x0400)
typedef unsigned char                           SQLTIMEWITHTIMEZONE;
typedef unsigned char                           SQLTIMESTAMPWITHTIMEZONE;
#endif /* ODBCVER >= 0x0400 */

/* function return type */
typedef SQLSMALLINT                             SQLRETURN;

/* generic data structures */
#if (ODBCVER >= 0x0300)
typedef void*                                   SQLHANDLE;
typedef SQLHANDLE                               SQLHENV;
typedef SQLHANDLE                               SQLHDBC;
typedef SQLHANDLE                               SQLHSTMT;
typedef SQLHANDLE                               SQLHDESC;
#else //ODBCVER < 0x0300
typedef void*                                   SQLHENV;
typedef void*                                   SQLHDBC;
typedef void*                                   SQLHSTMT;
#endif /* ODBCVER >= 0x0300 */

/* SQL portable types for C */
typedef unsigned char                           UCHAR;
typedef signed char                             SCHAR;
typedef signed short int                        SWORD;
typedef unsigned short int                      UWORD;
#if (SIZEOF_LONG_INT == 4)
typedef long int                                SDWORD;
typedef unsigned long int                       UDWORD;
#else
typedef int                                     SDWORD;
typedef unsigned int                            UDWORD;
#endif

typedef signed long                             SLONG;
typedef signed short                            SSHORT;
typedef unsigned long                           ULONG;
typedef unsigned short                          USHORT;
typedef double                                  SDOUBLE;
typedef double                                  LDOUBLE;
typedef float                                   SFLOAT;

typedef void*                                   PTR;

typedef void*                                   HENV;
typedef void*                                   HDBC;
typedef void*                                   HSTMT;

typedef signed short                            RETCODE;

typedef SQLPOINTER                              SQLHWND;

#ifndef    __SQLDATE
#define    __SQLDATE
/* transfer types for DATE, TIME, TIMESTAMP */
typedef struct tagDATE_STRUCT
{
    SQLSMALLINT    year;
    SQLUSMALLINT   month;
    SQLUSMALLINT   day;
} DATE_STRUCT;

#if (ODBCVER >= 0x0300)
typedef DATE_STRUCT                             SQL_DATE_STRUCT;
#endif  /* ODBCVER >= 0x0300 */

typedef struct tagTIME_STRUCT
{
    SQLUSMALLINT   hour;
    SQLUSMALLINT   minute;
    SQLUSMALLINT   second;
} TIME_STRUCT;

#if (ODBCVER >= 0x0300)
typedef TIME_STRUCT                             SQL_TIME_STRUCT;
#endif /* ODBCVER >= 0x0300 */

typedef struct tagTIMESTAMP_STRUCT
{
    SQLSMALLINT    year;
    SQLUSMALLINT   month;
    SQLUSMALLINT   day;
    SQLUSMALLINT   hour;
    SQLUSMALLINT   minute;
    SQLUSMALLINT   second;
    SQLUINTEGER    fraction;
} TIMESTAMP_STRUCT;

#if (ODBCVER >= 0x0300)
typedef TIMESTAMP_STRUCT                        SQL_TIMESTAMP_STRUCT;
#endif  /* ODBCVER >= 0x0300 */

/*
 * enumerations for DATETIME_INTERVAL_SUBCODE values for interval data types
 * these values are from SQL-92
 */

#if (ODBCVER >= 0x0300)
typedef enum
{
    SQL_IS_YEAR                                 = 1,
    SQL_IS_MONTH                                = 2,
    SQL_IS_DAY                                  = 3,
    SQL_IS_HOUR                                 = 4,
    SQL_IS_MINUTE                               = 5,
    SQL_IS_SECOND                               = 6,
    SQL_IS_YEAR_TO_MONTH                        = 7,
    SQL_IS_DAY_TO_HOUR                          = 8,
    SQL_IS_DAY_TO_MINUTE                        = 9,
    SQL_IS_DAY_TO_SECOND                        = 10,
    SQL_IS_HOUR_TO_MINUTE                       = 11,
    SQL_IS_HOUR_TO_SECOND                       = 12,
    SQL_IS_MINUTE_TO_SECOND                     = 13
} SQLINTERVAL;

#endif  /* ODBCVER >= 0x0300 */

#if (ODBCVER >= 0x0300)
typedef struct tagSQL_YEAR_MONTH
{
    SQLUINTEGER   year;
    SQLUINTEGER   month;
} SQL_YEAR_MONTH_STRUCT;

typedef struct tagSQL_DAY_SECOND
{
    SQLUINTEGER   day;
    SQLUINTEGER   hour;
    SQLUINTEGER   minute;
    SQLUINTEGER   second;
    SQLUINTEGER   fraction;
} SQL_DAY_SECOND_STRUCT;

typedef struct tagSQL_INTERVAL_STRUCT
{
    SQLINTERVAL   interval_type;
    SQLSMALLINT   interval_sign;
    union
    {
        SQL_YEAR_MONTH_STRUCT   year_month;
        SQL_DAY_SECOND_STRUCT   day_second;
    } intval;
} SQL_INTERVAL_STRUCT;

#endif  /* ODBCVER >= 0x0300 */

#endif    /* __SQLDATE    */

/* the ODBC C types for SQL_C_SBIGINT and SQL_C_UBIGINT */
#if (ODBCVER >= 0x0300)
#if (SIZEOF_LONG_INT == 8)
#define ODBCINT64                               long
#else
#define ODBCINT64                               long long
#endif

/* If using other compilers, define ODBCINT64 to the
   approriate 64 bit integer type */
#ifdef ODBCINT64
typedef ODBCINT64                               SQLBIGINT;
typedef unsigned ODBCINT64                      SQLUBIGINT;
#endif
#endif  /* ODBCVER >= 0x0300 */

/* internal representation of numeric data type */
#if (ODBCVER >= 0x0300)
#define SQL_MAX_NUMERIC_LEN                     16
typedef struct tagSQL_NUMERIC_STRUCT
{
    SQLCHAR    precision;
    SQLSCHAR   scale;
    SQLCHAR    sign;    /* 1 if positive, 0 if negative */
    SQLCHAR    val[SQL_MAX_NUMERIC_LEN];
} SQL_NUMERIC_STRUCT;
#endif  /* ODBCVER >= 0x0300 */

#if (ODBCVER >= 0x0350)
#ifdef GUID_DEFINED
typedef GUID                                    SQLGUID;
#else
/* size is 16 */
typedef struct  tagSQLGUID
{
    unsigned int     Data1;
    unsigned short   Data2;
    unsigned short   Data3;
    unsigned char    Data4[ 8 ];
} SQLGUID;
#endif  /* GUID_DEFINED */
#endif  /* ODBCVER >= 0x0350 */

typedef SQLULEN                                 BOOKMARK;

typedef unsigned short                          SQLWCHAR;





#ifdef UNICODE
typedef SQLWCHAR                                SQLTCHAR;
#else
typedef SQLCHAR                                 SQLTCHAR;
#endif  /* UNICODE */

#ifdef __cplusplus
}  /* End of extern "C" { */
#endif  /* __cplusplus */

#endif /* #ifndef __SQLTYPES_H */
