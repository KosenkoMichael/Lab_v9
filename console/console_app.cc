#include <iostream>
#include <functions/figure_functions.h>
#include <cstdlib>
#include <windows.h>

using namespace std;
using namespace kos;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice;
	FigureList figure_list;
	do {

		cout << "������� ����� ��������, ������� �� ������ �� ��������� >>>\n1 - �������� ������� � ������ �� ���������� �������\n"
			"2 - ������� ������� �� ������ �� ���������� �������\n3 - ������� ������ �� �����\n4 - ������ � ���������� �������\n0 - ��������� ������ ���������\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1: {
			Point cur_points[4];
			int type;
			cin >> type;
			for (int i = 0; i < 4; ++i) {
				cin >> cur_points[i].x >> cur_points[i].y;
			}
			int voult;
			cin >> voult;
			Figure figure;
			const auto ptr = figure.create((FigureType)type, cur_points);
			figure_list.figure_insert(ptr, voult);
		}
			break;
		case 2: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "������ ����" << "\n";
			}
			else {
				int choice_2;
				cin >> choice_2;
				figure_list.indexed_delete(choice_2);
			}
		}
			break;
		case 3: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "������ ����" << "\n";
			}
			else {
				figure_list.print();
			}
		}
			break;
		case 4: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "������ ����" << "\n";
			}
			else {
				cout << "1 - ���������� ��������� ������\n2 - ���������� ������� ������\n3 - ���������� ������������ ������������ ��������������"
					"\n4 - ����� ������ ������������ �������";
				int choice_3;
				cin >> choice_3;
				switch (choice_3) {
				case 1: {
					int index;
					cin >> index;
					cout << figure_list.indexed_get(index)->get_perim();
				}
					  break;
				case 2: {
					int index;
					cin >> index;
					cout << figure_list.indexed_get(index)->get_square();
				}
					  break;
				case 3: {
					int index;
					cin >> index;
					Figure framing_rectangle;
					framing_rectangle.set_min_framing_rectangle(*figure_list.indexed_get(index));
					framing_rectangle.print();
				}
					  break;
				case 4: {
					figure_list.max_square_search().print();
				}
					  break;
				}
			}
		}
			  break;
		}
	} while (choice != 0);
}