// Bars2STL.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*2.	Проверить, что в массиве есть хотя бы один элемент, равный заданному числу. Если такой элемент есть, найти его номер.*/

#include <iostream>
#include <Vector>
#include <List>
#include <String>
//#define complex
using namespace std;
class Complex {
public:
	int re, im;
public:
	Complex(int x = 0, int y = 0)
	{
		re = x;
		im = y;
	}
	bool operator ==(Complex x) {

		return ((re == x.re) && (im == x.im));
	}

	Complex& operator = (Complex& x) {
		re = x.re;
		im = x.im;
		return *this;
	}
	bool operator < (Complex& x) {

		return sqrt(pow(re, 2) + pow(im, 2)) < sqrt(pow(x.re, 2) + pow(x.im, 2));
	}
	friend ostream& operator <<(ostream& out, Complex x);
	friend istream& operator >>(istream& in, Complex& x);

};
ostream& operator <<(ostream& out, Complex x) {

	out << x.re << " " << x.im << "i\t";
	return out;

}
istream& operator >>(istream& in, Complex& x) {

	in >> x.re;
	in >> x.im;
	return in;

}
int main()
{
	setlocale(LC_ALL, "rus");
	string choose;
	cout << "введите 'v',если используем вектор, 'l', если список " << endl;
	while ((choose != "v") && (choose != "l"))
	{

		cin >> choose;
		if (choose == "v")
		{
#ifdef complex
			Complex elem;
			vector<Complex> vec;
#else
			int elem;
			vector <int> vec;

#endif 
			int size;
			cout << "сколько элементов добавить в вектор?\n";
			cin >> size;
			if (size > 0)
			{
				cout << "введите элементы\n";
				for (int i = 0; i < size; i++)
				{
					cin >> elem;
					vec.push_back(elem);
				}
				for (size_t i = 0; i < vec.size(); i++)
				{
					cout << vec[i];

				}
				cout << endl;
				cout << "введите элемент для поиска\n";
				cin >> elem;
				bool flg = false;
				for (size_t i = 0; i < vec.size(); i++)
				{
					if (vec[i] == elem)
					{
						flg = true;
						cout << "елемент " << elem << " находится по номеру " << i + 1 << endl;
					}
				}
				if (flg == false)
				{
					cout << "заданного элемента нет в массиве" << endl;
				}
			}
		}
		else if (choose == "l") {
#ifdef complex
			Complex elem;
			list<Complex> mylist;
#else
			int elem;
			list <int> mylist;

#endif 
			int size;
			cout << "сколько элементов добавить в список?\n";
			cin >> size;
			if (size > 0)
			{
				cout << "введите элементы\n";
				for (int i = 0; i < size; i++)
				{
					cin >> elem;
					mylist.push_back(elem);
				}
				for (auto i = mylist.begin(); i != mylist.end(); i++)
				{
					cout << *i;

				}
				cout << "введите элемент для поиска\n";
				cin >> elem;
				bool flg = false;
				int j = 0;
				for (auto i = mylist.begin(); i != mylist.end(); i++)
				{
					if (*i == elem)
					{
						flg = true;
						cout << "елемент " << elem << "находится на " << j + 1 << " месте с начала или на " << size - j << " с конца" << endl;
					}
					j++;
				}
				if (flg == false)
				{
					cout << "заданного элемента нет в списке" << endl;
				}

			}
		}
		else cout << "выберите v или l" << endl;
	}
	return 1;
}
