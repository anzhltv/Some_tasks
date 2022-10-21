// Экзамен29июня.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> A;
    int n;
    cout << "Vvedite kol-vo elementov v massive" << endl;
    cin >> n;
    A.resize(n);
    cout << "Kol-vo elementov v massive = " << A.size() << endl;
    int k = 0;
    cout << "Vvedite massiv: " << endl;
    vector<int>::iterator it;
    for (it = A.begin(); it != A.end(); it++)
    {
        cin >> *it;
    }
    for (int i = 0; i < A.size(); i++)
    {
        if (A[i] % 2 == 0)
        {
            k++;
        }
    }
    cout << "Kolichestvo chetnix chisel v konteinere=" << k << endl;
    vector<int>::reverse_iterator it1;
    cout << "Vivod v obratnom poryadke:  " << endl;
    for (it1 = A.rbegin(); it1 != A.rend(); it1++)
    {
        cout << *it1 << " ";
    }
    return(0);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
