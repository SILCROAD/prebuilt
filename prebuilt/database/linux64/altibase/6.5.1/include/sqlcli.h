/***********************************************************************
 * Copyright 1999-2006, Altibase Corporation or its subsidiaries.
 * All rights reserved.
 ***********************************************************************/

/***********************************************************************
 * $Id: sqlcli.h 69949 2015-03-26 07:33:36Z sparrow $
 ***********************************************************************/

#ifndef _O_ALTIBASE_SQL_CLI_H_
#define _O_ALTIBASE_SQL_CLI_H_ 1

#define HAVE_LONG_LONG

#if defined(_WIN64)
#define BUILD_REAL_64_BIT_MODE
#endif

#if defined(_MSC_VER)
#   include <windows.h>
#endif


#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 *  For WINDOWS old compilers such as VS60 and so forth,
 *  which do not have any information about SQLLEN series types.
 */
#if defined(_MSC_VER)
#if (_MSC_VER <= 1200)
#   if !defined(SQLLEN)
#       define  SQLLEN           SQLINTEGER
#       define  SQLULEN          SQLUINTEGER
#       define  SQLSETPOSIROW    SQLUSMALLINT
        typedef SQLULEN          SQLROWCOUNT;
        typedef SQLULEN          SQLROWSETSIZE;
        typedef SQLULEN          SQLTRANSID;
        typedef SQLLEN           SQLROWOFFSET;
#   endif /* if !defined(SQLLEN) */
#endif /* if (_MSC_VER <= 1200) */
#endif /* if defined(_MSC_VER) */

/*
 * -------------------------
 * Altibase specific types
 * -------------------------
 */

#define SQL_BLOB_LOCATOR        31
#define SQL_CLOB_LOCATOR        41
#define SQL_C_BLOB_LOCATOR      SQL_BLOB_LOCATOR
#define SQL_C_CLOB_LOCATOR      SQL_CLOB_LOCATOR

/*
 * Note : There is no type such as SQL_C_BLOB or SQL_C_CLOB.
 *        One shall make use of SQL_C_BINARY and SQL_C_CHAR instead.
 */

#define SQL_BLOB                30      /* SQL_LONGVARBINARY */
#define SQL_CLOB                40      /* SQL_LONGVARCHAR   */
#define SQL_BYTE                20001
#define SQL_VARBYTE             20003
#define SQL_NIBBLE              20002
#define SQL_GEOMETRY            10003
#define SQL_VARBIT              (-100)
#define SQL_NATIVE_TIMESTAMP    3010

#define SQL_BYTES               SQL_BYTE /* Deprecated !!! use SQL_BYTE instead */

/*
 * -----------------------------
 * Altibase specific attributes
 * -----------------------------
 */

#define ALTIBASE_DATE_FORMAT            2003
#define SQL_ATTR_FAILOVER               2004
#define ALTIBASE_NLS_USE                2005
#define ALTIBASE_EXPLAIN_PLAN           2006
#define SQL_ATTR_IDN_LANG               ALTIBASE_NLS_USE
#define SQL_ATTR_PORT		            2007

#define ALTIBASE_APP_INFO               2008
#define ALTIBASE_STACK_SIZE             2009

#define ALTIBASE_OPTIMIZER_MODE         2010

#define ALTIBASE_OPTIMIZER_MODE_UNKNOWN (0)
#define ALTIBASE_OPTIMIZER_MODE_COST    (1)
#define ALTIBASE_OPTIMIZER_MODE_RULE    (2)

#define ALTIBASE_UTRANS_TIMEOUT         2011
#define ALTIBASE_FETCH_TIMEOUT          2012
#define ALTIBASE_IDLE_TIMEOUT           2013
#define ALTIBASE_DDL_TIMEOUT            2044
#define ALTIBASE_HEADER_DISPLAY_MODE    2014

#define SQL_ATTR_LONGDATA_COMPAT        2015

#define ALTIBASE_CONN_ATTR_GPKIWORKDIR  2016
#define ALTIBASE_CONN_ATTR_GPKICONFDIR  2017
#define ALTIBASE_CONN_ATTR_USERCERT     2018
#define ALTIBASE_CONN_ATTR_USERKEY      2019
#define ALTIBASE_CONN_ATTR_USERAID      2020
#define ALTIBASE_CONN_ATTR_USERPASSWD   2021

#define ALTIBASE_XA_RMID                2022

#define ALTIBASE_STMT_ATTR_TOTAL_AFFECTED_ROWCOUNT   2023
#define ALTIBASE_CONN_ATTR_UNIXDOMAIN_FILEPATH       2024


#define ALTIBASE_XA_NAME                2025
#define ALTIBASE_XA_LOG_DIR             2026


#define ALTIBASE_STMT_ATTR_ATOMIC_ARRAY 2027


#define ALTIBASE_NLS_NCHAR_LITERAL_REPLACE           2028
#define ALTIBASE_NLS_CHARACTERSET                    2029
#define ALTIBASE_NLS_NCHAR_CHARACTERSET              2030
#define ALTIBASE_NLS_CHARACTERSET_VALIDATION         2031

#define ALTIBASE_CONN_ATTR_IPC_FILEPATH              2032

/* ALTIBASE UL FAIL-OVER */

#define ALTIBASE_ALTERNATE_SERVERS                   2033
#define ALTIBASE_LOAD_BALANCE                        2034
#define ALTIBASE_CONNECTION_RETRY_COUNT              2035
#define ALTIBASE_CONNECTION_RETRY_DELAY              2036
#define ALTIBASE_SESSION_FAILOVER                    2037
#define ALTIBASE_HEALTH_CHECK_DURATION               2038
#define ALTIBASE_FAILOVER_CALLBACK                   2039

#define ALTIBASE_PROTO_VER                           2040
#define ALTIBASE_PREFER_IPV6                         2041

#define ALTIBASE_MAX_STATEMENTS_PER_SESSION          2042
#define ALTIBASE_TRACELOG                            2043

#define ALTIBASE_DDL_TIMEOUT                         2044

#define SQL_CURSOR_HOLD                              2045
#define SQL_ATTR_CURSOR_HOLD                         SQL_CURSOR_HOLD

#define ALTIBASE_TIME_ZONE                           2046

#define SQL_ATTR_DEFERRED_PREPARE                    2047

#define ALTIBASE_LOB_CACHE_THRESHOLD                 2048

#define ALTIBASE_ODBC_COMPATIBILITY                  2049

#define ALTIBASE_FORCE_UNLOCK                        2050

#define ALTIBASE_ATTR_MULTI_STATEMENTS               2051

#define ALTIBASE_ENLIST_AS_TXCOOKIE                  2052

/* PROJ-2474 SSL/TLS */
#define ALTIBASE_SSL_CA                              2053
#define ALTIBASE_SSL_CAPATH                          2054
#define ALTIBASE_SSL_CERT                            2055
#define ALTIBASE_SSL_KEY                             2056
#define ALTIBASE_SSL_VERIFY                          2057
#define ALTIBASE_SSL_CIPHER                          2058
        

/*
 * STMT and DBC attributes that decide how many rows to prefetch
 * or how much memory to reserve as prefetch cache memory
 */
#define SQL_ATTR_PREFETCH_ROWS          12001
#define SQL_ATTR_PREFETCH_BLOCKS        12002
#define SQL_ATTR_PREFETCH_MEMORY        12003

/*
 * File option constants.
 * Used in a call to SQLBindFileToCol() or SQLBindFileToParam().
 */
#define SQL_FILE_CREATE     1
#define SQL_FILE_OVERWRITE  2
#define SQL_FILE_APPEND     3
#define SQL_FILE_READ       4

/*
 * Constants for indicator property of external procedure.
 */
#define ALTIBASE_EXTPROC_IND_NOTNULL    0
#define ALTIBASE_EXTPROC_IND_NULL       1

/*
 * ----------------------------
 * FailOver  Event Types.
 * ----------------------------
 */
#define ALTIBASE_FO_BEGIN               0
#define ALTIBASE_FO_END                 1
#define ALTIBASE_FO_ABORT               2
#define ALTIBASE_FO_GO                  3
#define ALTIBASE_FO_QUIT                4

 /*
 * ----------------------------
 * FailOver  Success Error Code.
 * ----------------------------
 must same as ul/msg/ulErrorCode.ih
 ulERR_ABORT_FAILOVER_SUCCESS = 0x51190096, (0x51190) (332176) */

#define ALTIBASE_FAILOVER_SUCCESS    332176
#define EMBEDED_ALTIBASE_FAILOVER_SUCCESS   (-332176)

/* Options for SQL_CURSOR_HOLD */
#define SQL_CURSOR_HOLD_ON        1
#define SQL_CURSOR_HOLD_OFF       0
#define SQL_CURSOR_HOLD_DEFAULT   SQL_CURSOR_HOLD_OFF

/* Options for ALTIBASE_EXPLAIN_PLAN */
#define ALTIBASE_EXPLAIN_PLAN_OFF   0
#define ALTIBASE_EXPLAIN_PLAN_ON    1
#define ALTIBASE_EXPLAIN_PLAN_ONLY  2

/* Options for ALTIBASE_ATTR_MULTI_STATEMENTS */
#define ALTIBASE_MULTI_STATEMENTS_OFF 0
#define ALTIBASE_MULTI_STATEMENTS_ON  1

/*
 * ----------------------------
 * Functions for handling LOB
 * ----------------------------
 */

#ifndef SQL_API
#   define SQL_API
#endif

SQLRETURN SQL_API SQLBindFileToCol(SQLHSTMT     aHandle,
                                   SQLSMALLINT  aColumnNumber,
                                   SQLCHAR     *aFileNameArray,
                                   SQLLEN      *aFileNameLengthArray,
                                   SQLUINTEGER *aFileOptionsArray,
                                   SQLLEN       aMaxFileNameLength,
                                   SQLLEN      *aLenOrIndPtr);

SQLRETURN SQL_API SQLBindFileToParam(SQLHSTMT     aHandle,
                                     SQLSMALLINT  aParameterNumber,
                                     SQLSMALLINT  aSqlType,
                                     SQLCHAR     *aFileNameArray,
                                     SQLLEN      *aFileNameLengthArray,
                                     SQLUINTEGER *aFileOptionsArray,
                                     SQLLEN       aMaxFileNameLength,
                                     SQLLEN      *aLenOrIndPtr);

SQLRETURN SQL_API SQLGetLobLength(SQLHSTMT     aHandle,
                                  SQLUBIGINT   aLocator,
                                  SQLSMALLINT  aLocatorCType,
                                  SQLUINTEGER *aLobLengthPtr);

SQLRETURN SQL_API SQLPutLob(SQLHSTMT     aHandle,
                            SQLSMALLINT  aLocatorCType,
                            SQLUBIGINT   aLocator,
                            SQLUINTEGER  aStartOffset,
                            SQLUINTEGER  aSizeToBeUpdated,
                            SQLSMALLINT  aSourceCType,
                            SQLPOINTER   aDataToPut,
                            SQLUINTEGER  aSizeDataToPut);

SQLRETURN SQL_API SQLGetLob(SQLHSTMT     aHandle,
                            SQLSMALLINT  aLocatorCType,
                            SQLUBIGINT   aLocator,
                            SQLUINTEGER  aStartOffset,
                            SQLUINTEGER  aSizeToGet,
                            SQLSMALLINT  aTargetCType,
                            SQLPOINTER   aBufferToStoreData,
                            SQLUINTEGER  aSizeBuffer,
                            SQLUINTEGER *aSizeReadPtr);

SQLRETURN SQL_API SQLFreeLob(SQLHSTMT aHandle, SQLUBIGINT aLocator);

SQLRETURN SQL_API SQLTrimLob(SQLHSTMT     aHandle,
                             SQLSMALLINT  aLocatorCType,
                             SQLUBIGINT   aLocator,
                             SQLUINTEGER  aStartOffset);


/*
 * ----------------------------------
 * Altibase Specific CLI Functions
 * ----------------------------------
 */

SQLRETURN SQL_API SQLGetPlan(SQLHSTMT aHandle, SQLCHAR **aPlan);


/*  Altibase UL Fail-Over, ConfigFile Loading Test function */
void  SQL_API   SQLDumpDataSources();
void  SQL_API   SQLDumpDataSourceFromName(SQLCHAR *aDataSourceName);


/* Altibase UL Fail-Over  */
typedef  SQLUINTEGER  (*SQLFailOverCallbackFunc)(SQLHDBC                       aDBC,
                                                 void                         *aAppContext,
                                                 SQLUINTEGER                   aFailOverEvent);
typedef   struct SQLFailOverCallbackContext
{
    SQLHDBC                  mDBC;
    void                    *mAppContext;
    SQLFailOverCallbackFunc  mFailOverCallbackFunc;
}SQLFailOverCallbackContext;

#if defined(_MSC_VER)
/* Altibase XA switch  */
extern struct xa_switch_t altibase_xa_switch;
#endif

/*
 * ----------------------------------
 * Altibase Connection Pool CLI Functions
 * ----------------------------------
 */
typedef SQLHANDLE SQLHDBCP;

SQLRETURN SQL_API SQLCPoolAllocHandle(SQLHDBCP *aConnectionPoolHandle);

SQLRETURN SQL_API SQLCPoolFreeHandle(SQLHDBCP aConnectionPoolHandle);

enum ALTIBASE_CPOOL_ATTR
{
    ALTIBASE_CPOOL_ATTR_MIN_POOL,
    ALTIBASE_CPOOL_ATTR_MAX_POOL,
    ALTIBASE_CPOOL_ATTR_IDLE_TIMEOUT,
    ALTIBASE_CPOOL_ATTR_CONNECTION_TIMEOUT,
    ALTIBASE_CPOOL_ATTR_DSN,
    ALTIBASE_CPOOL_ATTR_UID,
    ALTIBASE_CPOOL_ATTR_PWD,
    ALTIBASE_CPOOL_ATTR_TRACELOG,
    ALTIBASE_CPOOL_ATTR_VALIDATE_QUERY_TEXT,
    ALTIBASE_CPOOL_ATTR_VALIDATE_QUERY_RESULT,

    /* read-only */
    ALTIBASE_CPOOL_ATTR_TOTAL_CONNECTION_COUNT,
    ALTIBASE_CPOOL_ATTR_CONNECTED_CONNECTION_COUNT,
    ALTIBASE_CPOOL_ATTR_INUSE_CONNECTION_COUNT
};

enum ALTIBASE_TRACELOG_VALUE
{
    ALTIBASE_TRACELOG_NONE  = 0,
    ALTIBASE_TRACELOG_ERROR = 2,
    ALTIBASE_TRACELOG_FULL  = 4
};

SQLRETURN SQL_API SQLCPoolSetAttr(SQLHDBCP aConnectionPoolHandle,
        SQLINTEGER      aAttribute,
        SQLPOINTER      aValue,
        SQLINTEGER      aStringLength);

SQLRETURN SQL_API SQLCPoolGetAttr(SQLHDBCP aConnectionPoolHandle,
        SQLINTEGER      aAttribute,
        SQLPOINTER      aValue,
        SQLINTEGER      aBufferLength,
        SQLINTEGER      *aStringLength);

SQLRETURN SQL_API SQLCPoolInitialize(SQLHDBCP aConnectionPoolHandle);

SQLRETURN SQL_API SQLCPoolFinalize(SQLHDBCP aConnectionPoolHandle);

SQLRETURN SQL_API SQLCPoolGetConnection(SQLHDBCP aConnectionPoolHandle,
        SQLHDBC         *aConnectionHandle);

SQLRETURN SQL_API SQLCPoolReturnConnection(SQLHDBCP aConnectionPoolHandle,
        SQLHDBC         aConnectionHandle);

/* Only ADO.NET support */
SQLRETURN SQL_API SQLRowCountByMultiStmt( SQLHSTMT  StatementHandle,
                                          SQLLEN   *RowCount );

#ifdef __cplusplus
}
#endif
#endif

