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
		cout << "Введите номер действия, которое вы хотели бы совершить >>>\n1 - Вставить элемент в список по указанному индексу\n"
			"2 - Удалить элемент из списка по указанному индексу\n3 - Вывести список на экран\n4 - Работа с элементами массива\n0 - завершить работу программы\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1: {
			Figure figure;
			Point cur_points[4];
			int type;
			do {
				do {
					cout << "Введите тип фигуры >>>\n0 - ellipse\n1 - trapezoid\n2 - rectangle\n";
					cin >> type;
				} while ((type < 0) || (type > 2));
				cout << "Введите координаты точек фигуры >>>\n";
				for (int i = 0; i < 4; ++i) {
					cin >> cur_points[i].x >> cur_points[i].y;
				}
			} while (!(*figure.create((FigureType)type, cur_points)).check_figure());
			int voult;
			do {
				cout << "Введите индекс вставки (не более " << figure_list.get_size() <<")\n";
				cin >> voult;
			} while((voult<0)||(voult>figure_list.get_size()));
			const auto ptr = figure.create((FigureType)type, cur_points);
			figure_list.figure_insert(ptr, voult);
		}
			break;
		case 2: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "Массив пуст" << "\n";
			}
			else {
				int choice_2;
				do {
					cout << "Введите индекс удаления (не более " << figure_list.get_size()-1 << ")\n";
					cin >> choice_2;
				} while ((choice_2 < 0) || (choice_2 >= figure_list.get_size()));
				figure_list.indexed_delete(choice_2);
			}
		}
			break;
		case 3: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "Массив пуст" << "\n";
			}
			else {
				figure_list.print();
			}
		}
			break;
		case 4: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "Массив пуст" << "\n";
			}
			else {
				figure_list.print();
				cout << "\n";
				int choice_3;
				do {
					cout << "1 - вычисление периметра фигуры\n2 - вычисление площади фигуры\n3 - Вычисление минисального обрамляющего прямоугольника"
						"\n4 - Поиск фигуры максималтной площади";
					cin >> choice_3;
				} while ((choice_3<1) || (choice>4));
				switch (choice_3) {
				case 1: {
					int index;
					do {
						cout << "Введите индекс фигуры (не более " << figure_list.get_size()-1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.get_size()));
					cout << figure_list.indexed_get(index)->get_perim() <<"\n";
				}
					  break;
				case 2: {
					int index;
					do {
						cout << "Введите индекс фигуры (не более " << figure_list.get_size()-1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.get_size()));
					cout << figure_list.indexed_get(index)->get_square() << "\n";
				}
					  break;
				case 3: {
					int index;
					do {
						cout << "Введите индекс фигуры (не более " << figure_list.get_size()-1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.get_size()));
					Figure framing_rectangle;
					framing_rectangle.set_min_framing_rectangle(*figure_list.indexed_get(index));
					framing_rectangle.print();
					cout << "\n";
				}
					  break;
				case 4: {
					figure_list.max_square_search().print();
					cout << "\n";
				}
					  break;
				}
			}
		}
			  break;
		}
	} while (choice != 0);
}