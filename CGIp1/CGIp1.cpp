#include <windows.h>
#include <iostream>
#include <fstream>
#include <sql.h>
#include <sqlext.h>

int main()
{
	setlocale(LC_ALL, "RUS");
	printf("Content-Type: text/html\r\n\r\n");
	printf("<html> <head>\n");
	printf("<title>Пункт 1 CGI</title>\n");
	printf("</head>\n");
	printf("<body bgcolor=\"#FFFFFF\">\n");

	SQLRETURN rc;
	SQLHENV henv = NULL;
	SQLHDBC hdbc = NULL;
	SQLHSTMT hstmt = NULL;
	SQLWCHAR szConnStrOut[256];
	int iConnStrLength;
	HWND hwnd = GetDesktopWindow();
	rc = SQLAllocEnv(&henv);

	rc = SQLAllocConnect(henv, &hdbc);

	SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0); 
	WCHAR szConn[] = L"Driver={Microsoft Visual FoxPro Driver};SourceType=DBF;SourceDB=C:\\WEB5\\FOXPRO\\tastrade;Exclusive=No;Collate=Machine;NULL=NO;DELETED=NO;BACKGROUNDFETCH=NO;";

	rc = SQLDriverConnect(hdbc, NULL, (WCHAR*)szConn, SQL_NTS, (WCHAR*)szConnStrOut, 255, (SQLSMALLINT*)&iConnStrLength, SQL_DRIVER_NOPROMPT);
	if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
		rc = SQLAllocStmt(hdbc, &hstmt);
		if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
			printf("<H2><p align=\"center\">Таблица Покупатели</p></H2>\n");
			printf("<TABLE border=2 align=center bordercolor=Red>\n");
			printf("<td align=\"center\"><b>Айди</b></td>");
			printf("<td align=\"center\"><b>Имя</b></td>");
			printf("<td align=\"center\"><b>Город</b></td>");
			printf("<td align=\"center\"><b>Телефон</b></td>");
			printf("<td align=\"center\"><b>Макс заказ</b></td>");
			printf("</tr>\n");

			const int lenName1 = 50;
			const int lenName2 = 50;
			const int lenName3 = 50;
			const int lenName4 = 50;

			UCHAR Name1[lenName1];
			UCHAR Name2[lenName2];
			UCHAR Name3[lenName3];
			UCHAR Name4[lenName4];

			SQLINTEGER max_order;
		    SDWORD custom_id, c_name, city, phone, cbprod_id;
			SQLWCHAR selectStr[] = L"SELECT TOP 20 CUSTOMER_ID, CONTACT_NAME, CITY, PHONE, MAX_ORDER_AMT FROM [CUSTOMER.dbf] order by 1";///////*Order by 1LIMIT 20*/
			rc = SQLExecDirect(hstmt, selectStr, SQL_NTS);
		    SQLBindCol(hstmt, 1, SQL_WCHAR, &Name1, lenName1, &custom_id);
			SQLBindCol(hstmt, 2, SQL_WCHAR, &Name2, lenName2, &c_name);
			SQLBindCol(hstmt, 3, SQL_WCHAR, &Name3, lenName2, &city);
			SQLBindCol(hstmt, 4, SQL_WCHAR, &Name4, lenName4, &phone);
			SQLBindCol(hstmt, 5, SQL_INTEGER, &max_order, 0, &cbprod_id);
			while (true) {
				rc = SQLFetch(hstmt);
				printf("<tr align=center bgcolor=Cyan>\n");
				if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
					wprintf(L"<td align=left>");
					if (custom_id != SQL_NULL_DATA) wprintf(L"%s", Name1);
					else wprintf(L"");
					wprintf(L"</td>\n");

					wprintf(L"<td align=left>");
					if (c_name != SQL_NULL_DATA) wprintf(L"%s", Name2);
					else wprintf(L"");
					wprintf(L"</td>\n");
					wprintf(L"<td align=left>");
					if (city != SQL_NULL_DATA) wprintf(L"%s", Name3);
					else wprintf(L"");
					wprintf(L"</td>\n");

					wprintf(L"<td align=center>");
					if (phone != SQL_NULL_DATA) wprintf(L"%s", Name4);
					else wprintf(L"");
					wprintf(L"</td>\n");

					wprintf(L"<td align=right>");
					if (cbprod_id != SQL_NULL_DATA) wprintf(L"%i", max_order);
					else wprintf(L"");
					wprintf(L"</td>\n");

				}
				else { break; }
				printf("</tr>\n");
			}

			printf("</TABLE>\n");
		}

		SQLDisconnect(hdbc);
	}
	else wprintf(L"Couldn't connect C.\n");

	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);

	printf("</body></html>\n");
	return 0;
}


