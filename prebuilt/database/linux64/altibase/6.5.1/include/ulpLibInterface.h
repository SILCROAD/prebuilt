#ifndef _ULP_LIB_INTERFACE_
#define _ULP_LIB_INTERFACE_ 1

#if defined(_MSC_VER)
#include <winsock2.h>
#endif

#include <sqlcli.h>

#ifdef __cplusplus
# define EXTERN_C        extern "C"
#else
# define EXTERN_C
#endif

#define sqlca    (*ulpGetSqlca())
#define SQLCODE  (*ulpGetSqlcode())
#define SQLSTATE (*ulpGetSqlstate())
#define ssqlca   sqlca

#define SES_DUPKEY_ERR      (-69720)
#define SES_FILE_CREATE     SQL_FILE_CREATE
#define SES_FILE_OVERWRITE  SQL_FILE_OVERWRITE
#define SES_FILE_APPEND     SQL_FILE_APPEND
#define SES_FILE_READ       SQL_FILE_READ
#define APRE_DUPKEY_ERR     (-69720)
#define APRE_FILE_CREATE    SQL_FILE_CREATE
#define APRE_FILE_OVERWRITE SQL_FILE_OVERWRITE
#define APRE_FILE_APPEND    SQL_FILE_APPEND
#define APRE_FILE_READ      SQL_FILE_READ
#define MAX_CHAR_PTR        (65001)

typedef char APRE_BINARY;
typedef char APRE_BYTES;
typedef char APRE_VARBYTES;
typedef char APRE_NIBBLE;
typedef int  APRE_INTEGER;
typedef char APRE_NUMERIC;
typedef char APRE_BLOB;
typedef SQLUBIGINT APRE_BLOB_LOCATOR;
typedef char APRE_CLOB;
typedef SQLUBIGINT APRE_CLOB_LOCATOR;
typedef char APRE_BIT;

typedef char SES_BINARY;
typedef char SES_BYTES;
typedef char SES_VARBYTES;
typedef char SES_NIBBLE;
typedef int  SES_INTEGER;
typedef char SES_NUMERIC;
typedef char SES_BLOB;
typedef SQLUBIGINT SES_BLOB_LOCATOR;
typedef char SES_CLOB;
typedef SQLUBIGINT SES_CLOB_LOCATOR;
typedef char SES_BIT;

typedef struct { SQLLEN len; char arr[1]; } VARCHAR;
typedef struct { SQLLEN len; char arr[1]; } varchar;

typedef struct ulpSqlca
{
    char        sqlcaid[8];
    int         sqlcabc;
    int         sqlcode;
    struct
    {
        short   sqlerrml;
        char    sqlerrmc[2048];
    } sqlerrm;
    char        sqlerrp[8];
    int         sqlerrd[6];
    char        sqlwarn[8];
    char        sqlext[8];
} ulpSqlca;
typedef int  ulpSqlcode;
typedef char ulpSqlstate[6];
#define ses_sqlca ulpSqlca

typedef struct ulpHostVar
{
    void*  mHostVar;
    unsigned int mSizeof;
    unsigned int mLen;
    unsigned int mMaxlen;
    short  mUnsign;
    short  mInOut;
    short  mType;
    short  mIsDynAlloc;
    SQLLEN *mHostInd;
    SQLLEN *mVcInd;
    int    mMoreInfo;

    int isstruct;
    unsigned int structsize;
    int isarr;
    unsigned int arrsize;
    SQLUINTEGER *mFileopt;

    /* Padding for future growth */
    unsigned char filler[64];
} ulpHostVar;

typedef struct ulpSqlstmt
{
    /* Precompiler version */
    int ver;

    /* Embedded SQL info. */
    unsigned int  stmttype;
    char *stmt;
    char *stmtname;
    char *curname;
    char *extrastr;

    /* Error info. */
    ulpSqlca    *sqlcaerr;
    ulpSqlcode  *sqlcodeerr;
    ulpSqlstate *sqlstateerr;

    /* Info. of host variables */
    ulpHostVar *hostvalue;

    /* Binding info. of host variables */
    int isarr;
    unsigned int arrsize;
    int isstruct;
    unsigned int structsize;
    unsigned int iters;
    unsigned short numofhostvar;
    int sqlinfo;
    short scrollcur;

    unsigned int cursorscrollable;
    unsigned int cursorsensitivity;
    unsigned int cursorwithhold;

    void*  statusptr;
    void*  errcodeptr;
    int isatomic;
    int ismt;
    short *esqlopts;
    /* Padding for future growth */
    unsigned char filler[64];
} ulpSqlstmt;

EXTERN_C ulpSqlca    *ulpGetSqlca( void );
EXTERN_C ulpSqlcode  *ulpGetSqlcode( void );
EXTERN_C ulpSqlstate *ulpGetSqlstate( void );
EXTERN_C void         ulpDoEmsql( char *, ulpSqlstmt *, void * );
EXTERN_C void        *ulpAlign( void* aMemPtr, unsigned int aAlign );

#endif
