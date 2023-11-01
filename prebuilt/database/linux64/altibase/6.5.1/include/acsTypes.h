/***********************************************************************
 *
 * acsTypes.h
 * ACS (Altibase Call-level Spatio-temporal) Types
 *
 ***********************************************************************/

#ifndef __ACS_TYPES_H_
#define __ACS_TYPES_H_   (1)

#include <sqlcli.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------*
 * ODBC Type Re-Definition  
 *----------------------------------------------------------------*/

#ifndef _O_IDTYPES_H_
#define _O_IDTYPES_H_ 1

typedef SQLSCHAR       SChar;      /* Signed   char       8-bits */
typedef SQLCHAR        UChar;      /* Unsigned char       8-bits */
typedef SQLSMALLINT    SShort;     /* Signed   small int 16-bits */
typedef SQLUSMALLINT   UShort;     /* Unsigned small int 16-bits */
typedef SQLINTEGER     SInt;       /* Signed   integer   32-bits */
typedef SQLUINTEGER    UInt;       /* Unsigned integer   32-bits */
typedef SQLBIGINT      SLong;      /* Signed   big int   64-bits */
typedef SQLUBIGINT     ULong;      /* Unsigned big int   64-bits */
typedef SQLREAL        SFloat;     /* Signed   float     32-bits */  
typedef SQLDOUBLE      SDouble;    /* Signed   double    64-bits */

#endif /* _O_IDTYPES_H_ */

typedef struct stdDateType
{
   SShort year;
   UShort mon_day_hour;
   UInt   min_sec_mic;
} stdDateType;

/*----------------------------------------------------------------*
 * TODO - Automatic Generation
 *----------------------------------------------------------------*/

/*----------------------------------------------------------------*
 * ACS Type Definition
 *----------------------------------------------------------------*/

#include <ulsPrimTypes.i>

/*----------------------------------------------------------------
 * Native Geometry Types
 *----------------------------------------------------------------*/

#include <stdNativeTypes.i>

/*----------------------------------------------------------------
 * WKB Geometry Types
 *----------------------------------------------------------------*/

#include <stdWKBTypes.i>

#if defined(__cplusplus)
}
#endif

#endif /* __ACS_TYPES_H_ */

