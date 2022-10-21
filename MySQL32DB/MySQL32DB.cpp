#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;


void DisplayError(SQLSMALLINT t, SQLHSTMT h) {
    SQLWCHAR       SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
    SQLINTEGER    NativeError;
    SQLSMALLINT   i, MsgLen;
    SQLRETURN     rc;

    SQLLEN numRecs = 0;
    SQLGetDiagField(t, h, 0, SQL_DIAG_NUMBER, &numRecs, 0, 0);

    // Get the status records.
    i = 1;
    while (i <= numRecs && (rc = SQLGetDiagRec(t, h, i, SqlState, &NativeError,
        Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
        wprintf(L"Error %d: %s\n", NativeError, Msg);
        i++;
    }

}

int main() {
    SQLHENV henv;
    SQLHDBC hdbc = nullptr;
    SQLHSTMT hstmt = nullptr;
    SQLRETURN retcode;

    SQLWCHAR OutConnStr[1024];
    SQLSMALLINT OutConnStrLen;

    setlocale(LC_ALL, "Russian");
    // Allocate environment handle
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

    //  Set the ODBC version environment attribute
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

        // Allocate connection handle
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

            //  Set login timeout to 5 seconds
            if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

                SQLWCHAR     strConnect[256] = L"DSN=ODBSUN;SERVER=localhost;UID=root;PWD=1234;DRIVER=MySQL ODBC 8.0 Unicode;";
                // SQLWCHAR     strConnect[256] = L"DRIVER={MySQL ODBC 8.0 Unicode};SERVER=localhost;Database=sys;UID=root;PWD=1234;Options=3;";
                SQLWCHAR     strConnectOut[1024] = { 0 };
                SQLSMALLINT nNumOut = 0;
                SQLRETURN retcode = SQLDriverConnect(hdbc, NULL, (SQLWCHAR*)strConnect, SQL_NTS, (SQLWCHAR*)strConnectOut, sizeof(strConnectOut), &nNumOut, SQL_DRIVER_COMPLETE);

                // Allocate statement handle
                if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

                    // Process data
                    SQLHSTMT handleStatement = SQL_NULL_HSTMT;


                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, (SQLHANDLE*)&handleStatement);
                    // some error handling

                // Create a new database and use that

                    SQLWCHAR     createq[256] = L"CREATE DATABASE Foobar";
                    SQLWCHAR     create2[256] = L"USE Foobar";
                    SQLWCHAR     create3[256] = L"CREATE TABLE Wallet (WalletID int NOT NULL,  Name nvarchar(5) NOT NULL)";
                    retcode = SQLExecDirect(handleStatement, (SQLWCHAR*)createq, SQL_NTS);
                    retcode = SQLExecDirect(handleStatement, (SQLWCHAR*)create2, SQL_NTS);
                    retcode = SQLExecDirect(handleStatement, (SQLWCHAR*)create3, SQL_NTS);


                }

            }
            else {
                cout << "Query execution error." << endl;
            }

            SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
            SQLDisconnect(hdbc);
        }
        else {
            cout << "Connection error" << endl;
            DisplayError(SQL_HANDLE_DBC, hdbc);
        }
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);


        SQLFreeHandle(SQL_HANDLE_ENV, henv);
    }

    system("pause");
    return 0;
}
