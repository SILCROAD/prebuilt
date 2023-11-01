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

#ifndef __SQLUCODE_H
#define __SQLUCODE_H 1

#ifdef __cplusplus
extern "C" {  /* Assume C declarations for C++   */
#endif  /* __cplusplus */

#include <sqlext.h>

#define SQL_WCHAR                               (-8)
#define SQL_WVARCHAR                            (-9)
#define SQL_WLONGVARCHAR                        (-10)
#define SQL_C_WCHAR                             SQL_WCHAR

#ifdef UNICODE
#define SQL_C_TCHAR                             SQL_C_WCHAR
#else
#define SQL_C_TCHAR                             SQL_C_CHAR
#endif

#define SQL_SQLSTATE_SIZEW                      10  /* size of SQLSTATE for unicode */

// UNICODE versions
SQLRETURN SQL_API SQLColAttributeW(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       iCol,
    SQLUSMALLINT       iField,
    SQLPOINTER         pCharAttr,
    SQLSMALLINT        cbDescMax,
    SQLSMALLINT       *pcbCharAttr,
    SQLLEN            *pNumAttr);

SQLRETURN SQL_API SQLColAttributesW(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLUSMALLINT       fDescType,
    SQLPOINTER         rgbDesc,
    SQLSMALLINT        cbDescMax,
    SQLSMALLINT       *pcbDesc,
    SQLLEN            *pfDesc);

SQLRETURN SQL_API SQLConnectW(
    SQLHDBC            hdbc,
    SQLWCHAR          *szDSN,
    SQLSMALLINT        cchDSN,
    SQLWCHAR          *szUID,
    SQLSMALLINT        cchUID,
    SQLWCHAR          *szAuthStr,
    SQLSMALLINT        cchAuthStr);

SQLRETURN SQL_API SQLDescribeColW(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLWCHAR          *szColName,
    SQLSMALLINT        cchColNameMax,
    SQLSMALLINT       *pcchColName,
    SQLSMALLINT       *pfSqlType,
    SQLULEN           *pcbColDef,
    SQLSMALLINT       *pibScale,
    SQLSMALLINT       *pfNullable);

SQLRETURN SQL_API SQLErrorW(
    SQLHENV            henv,
    SQLHDBC            hdbc,
    SQLHSTMT           hstmt,
    SQLWCHAR         *wszSqlState,
    SQLINTEGER       *pfNativeError,
    SQLWCHAR         *wszErrorMsg,
    SQLSMALLINT       cchErrorMsgMax,
    SQLSMALLINT      *pcchErrorMsg);

SQLRETURN SQL_API SQLExecDirectW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szSqlStr,
    SQLINTEGER         TextLength);

SQLRETURN SQL_API SQLGetConnectAttrW(
    SQLHDBC            hdbc,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER        *pcbValue);

SQLRETURN SQL_API SQLGetCursorNameW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCursor,
    SQLSMALLINT        cchCursorMax,
    SQLSMALLINT       *pcchCursor);

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API SQLSetDescFieldW(
    SQLHDESC           DescriptorHandle,
    SQLSMALLINT        RecNumber,
    SQLSMALLINT        FieldIdentifier,
    SQLPOINTER         Value,
    SQLINTEGER         BufferLength);

SQLRETURN SQL_API SQLGetDescFieldW(
    SQLHDESC           hdesc,
    SQLSMALLINT        iRecord,
    SQLSMALLINT        iField,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbBufferLength,
    SQLINTEGER        *StringLength);

SQLRETURN SQL_API SQLGetDescRecW(
    SQLHDESC           hdesc,
    SQLSMALLINT        iRecord,
    SQLWCHAR          *szName,
    SQLSMALLINT        cchNameMax,
    SQLSMALLINT       *pcchName,
    SQLSMALLINT       *pfType,
    SQLSMALLINT       *pfSubType,
    SQLLEN            *pLength,
    SQLSMALLINT       *pPrecision,
    SQLSMALLINT       *pScale,
    SQLSMALLINT       *pNullable);

SQLRETURN SQL_API SQLGetDiagFieldW(
    SQLSMALLINT        fHandleType,
    SQLHANDLE          handle,
    SQLSMALLINT        iRecord,
    SQLSMALLINT        fDiagField,
    SQLPOINTER         rgbDiagInfo,
    SQLSMALLINT        cbBufferLength,
    SQLSMALLINT       *pcbStringLength);

SQLRETURN SQL_API SQLGetDiagRecW(
    SQLSMALLINT        fHandleType,
    SQLHANDLE          handle,
    SQLSMALLINT        iRecord,
    SQLWCHAR          *szSqlState,
    SQLINTEGER        *pfNativeError,
    SQLWCHAR          *szErrorMsg,
    SQLSMALLINT        cchErrorMsgMax,
    SQLSMALLINT       *pcchErrorMsg);
#endif

SQLRETURN SQL_API SQLPrepareW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szSqlStr,
    SQLINTEGER         cchSqlStr);

SQLRETURN SQL_API SQLSetConnectAttrW(
    SQLHDBC            hdbc,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValue);

SQLRETURN SQL_API SQLSetCursorNameW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCursor,
    SQLSMALLINT        cchCursor);

SQLRETURN SQL_API SQLColumnsW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName,
    SQLWCHAR          *szColumnName,
    SQLSMALLINT        cchColumnName);

SQLRETURN SQL_API SQLGetConnectOptionW(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLPOINTER         pvParam);

SQLRETURN SQL_API SQLGetInfoW(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fInfoType,
    SQLPOINTER         rgbInfoValue,
    SQLSMALLINT        cbInfoValueMax,
    SQLSMALLINT       *pcbInfoValue);

SQLRETURN SQL_API   SQLGetTypeInfoW(
    SQLHSTMT           StatementHandle,
    SQLSMALLINT        DataType);

SQLRETURN SQL_API SQLSetConnectOptionW(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLULEN            vParam);

SQLRETURN SQL_API SQLSpecialColumnsW(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fColType,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName,
    SQLUSMALLINT       fScope,
    SQLUSMALLINT       fNullable);

SQLRETURN SQL_API SQLStatisticsW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName,
    SQLUSMALLINT       fUnique,
    SQLUSMALLINT       fAccuracy);

SQLRETURN SQL_API SQLTablesW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName,
    SQLWCHAR          *szTableType,
    SQLSMALLINT        cchTableType);

SQLRETURN SQL_API SQLDataSourcesW(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLWCHAR          *szDSN,
    SQLSMALLINT        cchDSNMax,
    SQLSMALLINT       *pcchDSN,
    SQLWCHAR          *wszDescription,
    SQLSMALLINT        cchDescriptionMax,
    SQLSMALLINT       *pcchDescription);

SQLRETURN SQL_API SQLDriverConnectW(
    SQLHDBC            hdbc,
    SQLHWND            hwnd,
    SQLWCHAR          *szConnStrIn,
    SQLSMALLINT        cchConnStrIn,
    SQLWCHAR          *szConnStrOut,
    SQLSMALLINT        cchConnStrOutMax,
    SQLSMALLINT       *pcchConnStrOut,
    SQLUSMALLINT       fDriverCompletion);

SQLRETURN SQL_API SQLBrowseConnectW(
    SQLHDBC            hdbc,
    SQLWCHAR          *szConnStrIn,
    SQLSMALLINT        cchConnStrIn,
    SQLWCHAR          *szConnStrOut,
    SQLSMALLINT        cchConnStrOutMax,
    SQLSMALLINT*       pcchConnStrOut);

SQLRETURN SQL_API SQLColumnPrivilegesW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName,
    SQLWCHAR          *szColumnName,
    SQLSMALLINT        cchColumnName);

SQLRETURN SQL_API SQLGetStmtAttrW(
    SQLHSTMT           hstmt,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER        *pcbValue);

SQLRETURN SQL_API SQLSetStmtAttrW(
    SQLHSTMT           hstmt,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax);

SQLRETURN SQL_API SQLForeignKeysW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szPkCatalogName,
    SQLSMALLINT        cchPkCatalogName,
    SQLWCHAR          *szPkSchemaName,
    SQLSMALLINT        cchPkSchemaName,
    SQLWCHAR          *szPkTableName,
    SQLSMALLINT        cchPkTableName,
    SQLWCHAR          *szFkCatalogName,
    SQLSMALLINT        cchFkCatalogName,
    SQLWCHAR          *szFkSchemaName,
    SQLSMALLINT        cchFkSchemaName,
    SQLWCHAR          *szFkTableName,
    SQLSMALLINT        cchFkTableName);

SQLRETURN SQL_API SQLNativeSqlW(
    SQLHDBC            hdbc,
    SQLWCHAR          *szSqlStrIn,
    SQLINTEGER         cchSqlStrIn,
    SQLWCHAR          *szSqlStr,
    SQLINTEGER         cchSqlStrMax,
    SQLINTEGER        *pcchSqlStr);

SQLRETURN SQL_API SQLPrimaryKeysW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName);

SQLRETURN SQL_API SQLProcedureColumnsW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szProcName,
    SQLSMALLINT        cchProcName,
    SQLWCHAR          *szColumnName,
    SQLSMALLINT        cchColumnName);

SQLRETURN SQL_API SQLProceduresW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szProcName,
    SQLSMALLINT        cchProcName);

SQLRETURN SQL_API SQLTablePrivilegesW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTableName,
    SQLSMALLINT        cchTableName);

SQLRETURN SQL_API SQLDriversW(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLWCHAR          *szDriverDesc,
    SQLSMALLINT        cchDriverDescMax,
    SQLSMALLINT       *pcchDriverDesc,
    SQLWCHAR          *szDriverAttributes,
    SQLSMALLINT        cchDrvrAttrMax,
    SQLSMALLINT       *pcchDrvrAttr);

#if (ODBCVER >= 0x0400)
SQLRETURN SQL_API SQLStructuredTypesW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTypeName,
    SQLSMALLINT        cchTypeName);

SQLRETURN SQL_API SQLStructuredTypeColumnsW(
    SQLHSTMT           hstmt,
    SQLWCHAR          *szCatalogName,
    SQLSMALLINT        cchCatalogName,
    SQLWCHAR          *szSchemaName,
    SQLSMALLINT        cchSchemaName,
    SQLWCHAR          *szTypeName,
    SQLSMALLINT        cchTypeName,
    SQLWCHAR          *szColumnName,
    SQLSMALLINT        cchColumnName);
#endif /* ODBCVER >= 0x0400 */

// ANSI versions
SQLRETURN SQL_API SQLColAttributeA(
    SQLHSTMT           hstmt,
    SQLSMALLINT        iCol,
    SQLSMALLINT        iField,
    SQLPOINTER         pCharAttr,
    SQLSMALLINT        cbCharAttrMax,
    SQLSMALLINT       *pcbCharAttr,
    SQLLEN            *pNumAttr);

SQLRETURN SQL_API SQLColAttributesA(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLUSMALLINT       fDescType,
    SQLPOINTER         rgbDesc,
    SQLSMALLINT        cbDescMax,
    SQLSMALLINT       *pcbDesc,
    SQLLEN            *pfDesc);

SQLRETURN SQL_API SQLConnectA(
    SQLHDBC            hdbc,
    SQLCHAR           *szDSN,
    SQLSMALLINT        cbDSN,
    SQLCHAR           *szUID,
    SQLSMALLINT        cbUID,
    SQLCHAR           *szAuthStr,
    SQLSMALLINT        cbAuthStr);

SQLRETURN SQL_API SQLDescribeColA(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       icol,
    SQLCHAR           *szColName,
    SQLSMALLINT        cbColNameMax,
    SQLSMALLINT       *pcbColName,
    SQLSMALLINT       *pfSqlType,
    SQLULEN           *pcbColDef,
    SQLSMALLINT       *pibScale,
    SQLSMALLINT       *pfNullable);

SQLRETURN SQL_API SQLErrorA(
    SQLHENV            henv,
    SQLHDBC            hdbc,
    SQLHSTMT           hstmt,
    SQLCHAR           *szSqlState,
    SQLINTEGER        *pfNativeError,
    SQLCHAR           *szErrorMsg,
    SQLSMALLINT        cbErrorMsgMax,
    SQLSMALLINT       *pcbErrorMsg);

SQLRETURN SQL_API SQLExecDirectA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szSqlStr,
    SQLINTEGER         cbSqlStr);

SQLRETURN SQL_API SQLGetConnectAttrA(
    SQLHDBC            hdbc,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER        *pcbValue);

SQLRETURN SQL_API SQLGetCursorNameA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCursor,
    SQLSMALLINT        cbCursorMax,
    SQLSMALLINT       *pcbCursor);

#if (ODBCVER >= 0x0300)
SQLRETURN SQL_API SQLGetDescFieldA(
    SQLHDESC           hdesc,
    SQLSMALLINT        iRecord,
    SQLSMALLINT        iField,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbBufferLength,
    SQLINTEGER        *StringLength);

SQLRETURN SQL_API SQLGetDescRecA(
    SQLHDESC           hdesc,
    SQLSMALLINT        iRecord,
    SQLCHAR           *szName,
    SQLSMALLINT        cbNameMax,
    SQLSMALLINT       *pcbName,
    SQLSMALLINT       *pfType,
    SQLSMALLINT       *pfSubType,
    SQLLEN            *pLength,
    SQLSMALLINT       *pPrecision,
    SQLSMALLINT       *pScale,
    SQLSMALLINT       *pNullable);

SQLRETURN SQL_API SQLGetDiagFieldA(
    SQLSMALLINT        fHandleType,
    SQLHANDLE          handle,
    SQLSMALLINT        iRecord,
    SQLSMALLINT        fDiagField,
    SQLPOINTER         rgbDiagInfo,
    SQLSMALLINT        cbDiagInfoMax,
    SQLSMALLINT       *pcbDiagInfo);

SQLRETURN SQL_API SQLGetDiagRecA(
    SQLSMALLINT        fHandleType,
    SQLHANDLE          handle,
    SQLSMALLINT        iRecord,
    SQLCHAR           *szSqlState,
    SQLINTEGER        *pfNativeError,
    SQLCHAR           *szErrorMsg,
    SQLSMALLINT        cbErrorMsgMax,
    SQLSMALLINT       *pcbErrorMsg);

SQLRETURN SQL_API SQLGetStmtAttrA(
    SQLHSTMT           hstmt,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValueMax,
    SQLINTEGER        *pcbValue);
#endif

SQLRETURN SQL_API   SQLGetTypeInfoA(
    SQLHSTMT           StatementHandle,
    SQLSMALLINT        DataType);

SQLRETURN SQL_API SQLPrepareA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szSqlStr,
    SQLINTEGER         cbSqlStr);

SQLRETURN SQL_API SQLSetConnectAttrA(
    SQLHDBC            hdbc,
    SQLINTEGER         fAttribute,
    SQLPOINTER         rgbValue,
    SQLINTEGER         cbValue);

SQLRETURN SQL_API SQLSetCursorNameA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCursor,
    SQLSMALLINT        cbCursor);

SQLRETURN SQL_API SQLColumnsA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName,
    SQLCHAR           *szColumnName,
    SQLSMALLINT        cbColumnName);

SQLRETURN SQL_API SQLGetConnectOptionA(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLPOINTER         pvParam);

SQLRETURN SQL_API SQLGetInfoA(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fInfoType,
    SQLPOINTER         rgbInfoValue,
    SQLSMALLINT        cbInfoValueMax,
    SQLSMALLINT       *pcbInfoValue);

SQLRETURN SQL_API SQLGetStmtOptionA(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fOption,
    SQLPOINTER         pvParam);

SQLRETURN SQL_API SQLSetConnectOptionA(
    SQLHDBC            hdbc,
    SQLUSMALLINT       fOption,
    SQLULEN            vParam);

SQLRETURN SQL_API SQLSetStmtOptionA(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fOption,
    SQLULEN            vParam);

SQLRETURN SQL_API SQLSpecialColumnsA(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       fColType,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName,
    SQLUSMALLINT       fScope,
    SQLUSMALLINT       fNullable);

SQLRETURN SQL_API SQLStatisticsA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName,
    SQLUSMALLINT       fUnique,
    SQLUSMALLINT       fAccuracy);

SQLRETURN SQL_API SQLTablesA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName,
    SQLCHAR           *szTableType,
    SQLSMALLINT        cbTableType);

SQLRETURN SQL_API SQLDataSourcesA(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLCHAR           *szDSN,
    SQLSMALLINT        cbDSNMax,
    SQLSMALLINT       *pcbDSN,
    SQLCHAR           *szDescription,
    SQLSMALLINT        cbDescriptionMax,
    SQLSMALLINT       *pcbDescription);

SQLRETURN SQL_API SQLDriverConnectA(
    SQLHDBC            hdbc,
    SQLHWND            hwnd,
    SQLCHAR           *szConnStrIn,
    SQLSMALLINT        cbConnStrIn,
    SQLCHAR           *szConnStrOut,
    SQLSMALLINT        cbConnStrOutMax,
    SQLSMALLINT       *pcbConnStrOut,
    SQLUSMALLINT       fDriverCompletion);

SQLRETURN SQL_API SQLBrowseConnectA(
    SQLHDBC            hdbc,
    SQLCHAR           *szConnStrIn,
    SQLSMALLINT        cbConnStrIn,
    SQLCHAR           *szConnStrOut,
    SQLSMALLINT        cbConnStrOutMax,
    SQLSMALLINT       *pcbConnStrOut);

SQLRETURN SQL_API SQLColumnPrivilegesA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName,
    SQLCHAR           *szColumnName,
    SQLSMALLINT        cbColumnName);

SQLRETURN SQL_API SQLDescribeParamA(
    SQLHSTMT           hstmt,
    SQLUSMALLINT       ipar,
    SQLSMALLINT       *pfSqlType,
    SQLUINTEGER       *pcbParamDef,
    SQLSMALLINT       *pibScale,
    SQLSMALLINT       *pfNullable);

SQLRETURN SQL_API SQLForeignKeysA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szPkCatalogName,
    SQLSMALLINT        cbPkCatalogName,
    SQLCHAR           *szPkSchemaName,
    SQLSMALLINT        cbPkSchemaName,
    SQLCHAR           *szPkTableName,
    SQLSMALLINT        cbPkTableName,
    SQLCHAR           *szFkCatalogName,
    SQLSMALLINT        cbFkCatalogName,
    SQLCHAR           *szFkSchemaName,
    SQLSMALLINT        cbFkSchemaName,
    SQLCHAR           *szFkTableName,
    SQLSMALLINT        cbFkTableName);

SQLRETURN SQL_API SQLNativeSqlA(
    SQLHDBC            hdbc,
    SQLCHAR           *szSqlStrIn,
    SQLINTEGER         cbSqlStrIn,
    SQLCHAR           *szSqlStr,
    SQLINTEGER         cbSqlStrMax,
    SQLINTEGER        *pcbSqlStr);

SQLRETURN SQL_API SQLPrimaryKeysA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName);

SQLRETURN SQL_API SQLProcedureColumnsA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szProcName,
    SQLSMALLINT        cbProcName,
    SQLCHAR           *szColumnName,
    SQLSMALLINT        cbColumnName);

SQLRETURN SQL_API SQLProceduresA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szProcName,
    SQLSMALLINT        cbProcName);

SQLRETURN SQL_API SQLTablePrivilegesA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTableName,
    SQLSMALLINT        cbTableName);

SQLRETURN SQL_API SQLDriversA(
    SQLHENV            henv,
    SQLUSMALLINT       fDirection,
    SQLCHAR           *szDriverDesc,
    SQLSMALLINT        cbDriverDescMax,
    SQLSMALLINT       *pcbDriverDesc,
    SQLCHAR           *szDriverAttributes,
    SQLSMALLINT        cbDrvrAttrMax,
    SQLSMALLINT       *pcbDrvrAttr);

#if (ODBCVER >= 0x0400)
SQLRETURN SQL_API SQLStructuredTypesA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTypeName,
    SQLSMALLINT        cbTypeName);

SQLRETURN SQL_API SQLStructuredTypeColumnsA(
    SQLHSTMT           hstmt,
    SQLCHAR           *szCatalogName,
    SQLSMALLINT        cbCatalogName,
    SQLCHAR           *szSchemaName,
    SQLSMALLINT        cbSchemaName,
    SQLCHAR           *szTypeName,
    SQLSMALLINT        cbTypeName,
    SQLCHAR           *szColumnName,
    SQLSMALLINT cbColumnName);
#endif /* ODBCVER >= 0x0400 */
//---------------------------------------------
// Mapping macros for Unicode
//---------------------------------------------
#ifndef SQL_NOUNICODEMAP    // define this to disable the mapping
#ifdef  UNICODE

#define SQLColAttribute                         SQLColAttributeW
#define SQLColAttributes                        SQLColAttributesW
#define SQLConnect                              SQLConnectW
#define SQLDescribeCol                          SQLDescribeColW
#define SQLError                                SQLErrorW
#define SQLExecDirect                           SQLExecDirectW
#define SQLGetConnectAttr                       SQLGetConnectAttrW
#define SQLGetCursorName                        SQLGetCursorNameW
#define SQLGetDescField                         SQLGetDescFieldW
#define SQLGetDescRec                           SQLGetDescRecW
#define SQLGetDiagField                         SQLGetDiagFieldW
#define SQLGetDiagRec                           SQLGetDiagRecW
#define SQLPrepare                              SQLPrepareW
#define SQLSetConnectAttr                       SQLSetConnectAttrW
#define SQLSetCursorName                        SQLSetCursorNameW
#define SQLSetDescField                         SQLSetDescFieldW
#define SQLSetStmtAttr                          SQLSetStmtAttrW
#define SQLGetStmtAttr                          SQLGetStmtAttrW
#define SQLColumns                              SQLColumnsW
#define SQLGetConnectOption                     SQLGetConnectOptionW
#define SQLGetInfo                              SQLGetInfoW
#define SQLGetTypeInfo                          SQLGetTypeInfoW
#define SQLSetConnectOption                     SQLSetConnectOptionW
#define SQLSpecialColumns                       SQLSpecialColumnsW
#define SQLStatistics                           SQLStatisticsW
#define SQLStructuredTypes                      SQLStructuredTypesW
#define SQLStructuredTypeColumns                SQLStructuredTypeColumnsW
#define SQLTables                               SQLTablesW
#define SQLDataSources                          SQLDataSourcesW
#define SQLDriverConnect                        SQLDriverConnectW
#define SQLBrowseConnect                        SQLBrowseConnectW
#define SQLColumnPrivileges                     SQLColumnPrivilegesW
#define SQLForeignKeys                          SQLForeignKeysW
#define SQLNativeSql                            SQLNativeSqlW
#define SQLPrimaryKeys                          SQLPrimaryKeysW
#define SQLProcedureColumns                     SQLProcedureColumnsW
#define SQLProcedures                           SQLProceduresW
#define SQLTablePrivileges                      SQLTablePrivilegesW
#define SQLDrivers                              SQLDriversW

#endif  /* UNICODE */
#endif  /* SQL_NOUNICODEMAP */

#ifdef __cplusplus
}       /* End of extern "C" { */
#endif  /* __cplusplus */

#endif  /* #ifndef __SQLUCODE */
