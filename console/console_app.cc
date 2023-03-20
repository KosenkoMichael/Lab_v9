#include <iostream>
#include <functions/figure_functions.h>
#include <cstdlib>

using namespace std;
using namespace kos;

int main() {
	int choice;
	FigureList figure_list;
	do {
		cout << "Enter your choice >>>\n1 - Insert the element by index\n"
			"2 - Delete the element by index\n3 - Print the list\n4 - Work with elements\n0 - Exit the program\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1: {
			Figure figure;
			Point cur_points[4];
			float points[8];
			int type;
			int voult;
			int flag;
			do {
				flag = 0;
				do {
					cout << "Input index (0<= and no more than " << figure_list.get_size() << ")\n";
					cin >> voult;
				} while ((voult < 0) || (voult > figure_list.get_size()));
				do {
					cout << "Input type >>>\n0 - ellipse\n1 - trapezoid\n2 - rectangle\n";
					cin >> type;
				} while ((type < 0) || (type > 2));
				switch (type) {
				case ellipse: {
					cout << "Input point's coordinates >>>\n";
					for (int i = 0; i < 4; ++i)
						cin >> points[i];
					if (!(*figure.create_ellipse(points)).check_figure()) {
						cout << "Incorrect figure, try again\n";
							break;
					}
					const auto ptr = figure.create_ellipse(points);
					figure_list.figure_insert(ptr, voult);
					flag = 1;
				} break;
				case trapezoid: {
					cout << "Input point's coordinates >>>\n";
					for (int i = 0; i < 8; ++i)
						cin >> points[i];
					if (!(*figure.create_trapezoid(points)).check_figure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					const auto ptr = figure.create_trapezoid(points);
					figure_list.figure_insert(ptr, voult);
					flag = 1;
				} break;
				case rectangle: {
					cout << "Input point's coordinates >>>\n";
					for (int i = 0; i < 4; ++i)
						cin >> points[i];
					if (!(*figure.create_rectangle(points)).check_figure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					const auto ptr = figure.create_rectangle(points);
					figure_list.figure_insert(ptr, voult);
					flag = 1;
				} break;
				}
			} while (flag == 0);
		}
			break;
		case 2: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				int choice_2;
				do {
					cout << "Input index (0<= and no more than " << figure_list.get_size()-1 << ")\n";
					cin >> choice_2;
				} while ((choice_2 < 0) || (choice_2 >= figure_list.get_size()));
				figure_list.indexed_delete(choice_2);
			}
		}
			break;
		case 3: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				figure_list.print();
			}
		}
			break;
		case 4: {
			if (figure_list.get_size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				figure_list.print();
				cout << "\n";
				int choice_3;
				do {
					cout << "1 - Calculate perimetr\n2 - Calculate square\n3 - Print min framing rectangle"
						"\n4 - Search max square figure";
					cin >> choice_3;
				} while ((choice_3<1) || (choice>4));
				switch (choice_3) {
				case 1: {
					int index;
					do {
						cout << "Input index (0<= and no more than " << figure_list.get_size()-1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.get_size()));
					cout << figure_list.indexed_get(index)->get_perim() <<"\n";
				}
					  break;
				case 2: {
					int index;
					do {
						cout << "Input index (0<= and no more than " << figure_list.get_size()-1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.get_size()));
					cout << figure_list.indexed_get(index)->get_square() << "\n";
				}
					  break;
				case 3: {
					int index;
					do {
						cout << "Input index (0<= and no more than " << figure_list.get_size()-1 << ")\n";
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