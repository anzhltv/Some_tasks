// Bars4last.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//мультиграф	Последовательный алгоритм разрезания.
//Первый элемент на плату всегда назначается по указанию пользователя программы(вводится).
//Очередной элемент, выбираемый на плату, содержит минимальное число связей с элементами еще не назначенными на плату.


#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	ifstream fin;
	fin.open("circuit.txt");
	int N;
	fin >> N;
	int mN, mL;
	fin >> mN >> mL;
	vector<vector<int>> circuit(N);
	for (int i = 0; i < N; i++) {
		char t;
		circuit[i].resize(N);
		for (int j = 0; j < N; j++) {
			fin >> t;
			int t1 = t - '0';
			circuit[i][j] = t1;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << circuit[i][j] << ' ';
		}
		cout << "\n";
	}
	fin.close();

	
	vector<set<int>>cut;
	set<int>to_cut;
	set<int> cir;
	vector<int>add;
	for (int i = 0; i < N; i++)
		to_cut.insert(i);

	while (to_cut.size() != 0) { 
		add.clear();
		cut.resize(cut.size() + 1); 
		int t;
		for (set<int>::iterator i = to_cut.begin(); i != to_cut.end(); i++) {
			cout << *i + 1 << " "; 
		}
		cout << "\n";

		if (to_cut.size()) {
			cin >> t;
			t--;
			while (to_cut.find(t) == to_cut.end()) {
				cout << "элемент " << t + 1 << " уже распределен\n ";
				cin >> t;
				t--; \
			}
			cut.back().insert(t);
			to_cut.erase(t);
			add.push_back(t);
		}
		for (int i = 0; i < add.size(); i++) {
			for (int j = 0; j < N; j++) {
				if (circuit[i][j] && (cut.back().find(j) == cut.back().end()))
					cir.insert(j); 
			}
		}
		int step = (cir.size() <= mL ? 2 : 0);

		while ((to_cut.size() > 0) && (cut.back().size() < mN)) { 
			int  min = 21, min_i;
			for (auto i = to_cut.begin(); i != to_cut.end(); i++) {
				int c = 0;
				for (auto j = to_cut.begin(); j != to_cut.end(); j++) {
					if (circuit[*i][*j])
						c=c+circuit[*i][*j];
				}
				if (c < min) {
					min = c;
					min_i = *i;
				}
			}
			
			cut.back().insert(min_i);
			to_cut.erase(min_i);
			add.push_back(min_i);
			cir.clear();

			for (int i = 0; i < add.size(); i++) {
				for (int j = 0; j < N; j++) {
					if (circuit[i][j] && (cut.back().find(j) == cut.back().end()))
						cir.insert(j);
				}
			}
			if (cir.size() <= mL)
				step = add.size();
		}

		if (step == 0) {
			cout << "Разрезание невозможно";
			system("pause");
			break;
		}
		while (step < add.size()) {
			to_cut.insert(add.back());
			cut.back().erase(add.back());
			add.pop_back();
		}
	}

	for (int i = 0; i < cut.size(); i++) {
		cout << "Плата " << i + 1 << ": ";
		for (auto j = cut[i].begin(); j != cut[i].end(); j++) {
			cout << *j + 1 << " ";
		}
		cout << "\n";
	}
	system("pause");
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
