
#include <iostream>
#define __LCC__ 
#include <conio.h>
#include <stdlib.h>
#include <C:\Program Files\MySQL\MySQL Server 8.0\include\mysql.h>
#include<stdio.h>
#include <tchar.h>

#pragma comment(lib, "libmysql.lib")

using namespace std;

int main(int argc, _TCHAR* argv[])

{
	setlocale(0, "");
	system("cls");

	MYSQL_RES* res;
	MYSQL_ROW row;

	int i = 0;

	MYSQL* conn;
	//дескриптор соединения
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		// Если дескриптор не получен – сообщение об ошибке
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
	}
	// Подключаемся к серверу
	if (!mysql_real_connect(conn, "localhost", "root", "1234", "Connection4lab2", 3306, NULL, 0))
	{
		// Если невозможно установить соединение с сервером - сообщение об ошибке 
		fprintf(stderr, "Error: can'tconnecttodatabase %s\n", mysql_error(conn));
	}
	else
	{
		//Если успешно  - "Success!"
		fprintf(stdout, "Success!\n");


		mysql_set_character_set(conn, "ANSI");
		//Проверка кодировки
		cout << "connection character set: " << mysql_character_set_name(conn) << endl;

		mysql_query(conn, "SELECT * FROM покупатели"); //Делаем запрос к таблице по имени покупатели

		if (res = mysql_store_result(conn))
		{
			while (row = mysql_fetch_row(res))
			{
				for (i = 0; i < mysql_num_fields(res); i++)
				{
					cout << row[i] << '\t'; // Выводим все что есть в базе
				}
				cout << endl;
			}
		}
		else
			cerr << mysql_error(conn);
	}
	// Закрываем соединение с сервером базы данных
	mysql_close(conn);

	system("Pause");
	return 0;
}


