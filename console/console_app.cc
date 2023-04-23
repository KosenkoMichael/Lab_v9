#include <iostream>
#include <functions/figure_functions.h>
#include <cstdlib>

using namespace std;
using namespace kos;
void create_ellipse(float* ellipse_points, Point* points) {
	points[0].x = ellipse_points[0];
	points[0].y = points[2].y = ellipse_points[1];
	points[1].x = points[3].x = ellipse_points[2];
	points[1].y = ellipse_points[3];
	points[2].x = points[1].x * 2 - points[0].x;
	points[3].y = points[0].y * 2 - points[1].y;

}
void create_rectangle(float* rectangle_points, Point* points) {
	points[0].x = points[3].x = rectangle_points[0];
	points[0].y = points[1].y = rectangle_points[1];
	points[1].x = points[2].x = rectangle_points[2];
	points[2].y = points[3].y = rectangle_points[3];
}
void create_trapezoid(float* trapezoid_points, Point* points) {
	for (int i = 0, j = 0; i < 4; ++i) {
		points[i].x = trapezoid_points[j];
		points[i].y = trapezoid_points[j + 1];
		j += 2;
	}
}

int main() {
	int choice;
	FigureList figure_list;
	do {
		cout << "Enter your choice >>>\n1 - Insert the element by index\n"
			"2 - Delete the element by index\n3 - Print the list\n4 - Work with elements\n0 - Exit the program\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 1:
			int index;
			int type;
			float points[8];
			Point right_points[4];
			do {
				cout << " Input index, no less, than 0, and no more, than " << figure_list.size();
					cin >> index;
			} while ((index < 0) || (index > figure_list.size()));
			do {
				cout << " Input type, 0 - ellipse, 1 - trapezoid, 2 - rectangle";
				cin >> type;
			} while ((type < 0) || (type > 2));
			if (type == 1) {
				for (int i = 0; i < 8; ++i)
					cin >> points[i];
				create_trapezoid(points, right_points);
				Trapezoid trapezoid(right_points);
				if (!trapezoid.check_figure()) {
					cout << "Incorrect figure" << endl;
					break;
				}	
				figure_list.insert(make_shared<Trapezoid>(right_points), index);
				break;
			}
			else if (type == 0) {
				for (int i = 0; i < 4; ++i)
					cin >> points[i];
				create_ellipse(points, right_points);
				Ellipse ellipse(right_points);
				if (!ellipse.check_figure()) {
					cout << "Incorrect figure" << endl;
					break;
				}
				figure_list.insert(make_shared<Ellipse>(right_points), index);
				break;
			}
			else if (type == 2) {
				for (int i = 0; i < 4; ++i)
					cin >> points[i];
				create_rectangle(points, right_points);
				Rectangle rectangle(right_points);
				if (!rectangle.check_figure()) {
					cout << "Incorrect figure" << endl;
					break;
				}
				figure_list.insert(make_shared<Rectangle>(right_points), index);
				break;
			}
		case 2: {
			if (figure_list.size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				int choice_2;
				do {
					cout << "Input index (0<= and no more than " << figure_list.size() - 1 << ")\n";
					cin >> choice_2;
				} while ((choice_2 < 0) || (choice_2 >= figure_list.size()));
				figure_list.delete_figure(choice_2);
			}
		}
			  break;
		case 3: {
			if (figure_list.size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				/*figure_list.print();*/
				figure_list.print();
			}
		}
			  break;
		case 4: {
			if (figure_list.size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				/*figure_list.print();*/
				figure_list.print();
				cout << "\n";
				int choice_3;
				do {
					cout << "1 - Calculate perimetr\n2 - Calculate square\n3 - Print min framing rectangle"
						"\n4 - Search max square figure";
					cin >> choice_3;
				} while ((choice_3 < 1) || (choice > 4));
				switch (choice_3) {
				case 1: {
					int index;
					do {
						cout << "Input index (0<= and no more than " << figure_list.size() - 1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.size()));
					cout << figure_list[index]->get_perim() << "\n";
				}
					  break;
				case 2: {
					int index;
					do {
						cout << "Input index (0<= and no more than " << figure_list.size() - 1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.size()));
					cout << figure_list[index]->get_square() << "\n";
				}
					  break;
				case 3: {
					int index;
					do {
						cout << "Input index (0<= and no more than " << figure_list.size() - 1 << ")\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_list.size()));
					Point rec_points[4];
					figure_list[index]->set_min_framing_rectangle(rec_points);
					/*framing_rectangle.print();*/
					Rectangle framing_rectangle(rec_points);
					framing_rectangle.print();
					cout << "\n";
				}
					  break;
				case 4: {
					/*figure_list.max_square_search().print();*/
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