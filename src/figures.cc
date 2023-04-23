#include <functions/figure_functions.h>

#include <cmath>
#include<stdexcept>
#include<iostream>

#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) > (y) ? (y) : (x)

using namespace kos;

using namespace std;

float Point::p_len(Point point) {
	return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
}
Point* Figure::get_points() {
	return apex;
}

bool Figure::operator==(const Figure& rhs) {
	bool flag = true;
	for (int i = 0; i < 4; ++i) {
		if ((apex[i].x != rhs.apex[i].x) || (apex[i].y != rhs.apex[i].y))
			flag = false;
	}
	return flag;
}

Rectangle::Rectangle() {
	for (int i = 0; i < 4; ++i)
		apex[i].x = apex[i].y = 0;
}

Rectangle::Rectangle(Point* points) {
	for (int i = 0; i < 4; ++i) {
		apex[i] = points[i];
	}
}

float Rectangle::get_perim() {
	float perim = 0;
	for (int i = 0; i < 3; i++) {
		perim += apex[i].p_len(apex[i + 1]);
	}
	perim += apex[3].p_len(apex[0]);
	return perim;
}

float Rectangle::get_square() {
	return apex[0].p_len(apex[1]) * apex[0].p_len(apex[3]);
}

void Rectangle::set_min_framing_rectangle(Point* points) {
	for (int i = 0; i < 4; ++i)
		points[i] = apex[i];
}

bool Rectangle::check_figure() {
	return ((apex[0].x == apex[3].x) && (apex[1].x == apex[2].x) && (apex[0].y == apex[1].y) && (apex[3].y == apex[2].y) && (apex[0].x < apex[1].x) && (apex[0].y > apex[3].y));
}

void Rectangle::print() {
	cout << "rectangle" << " ";
	for (int i = 0; i < 4; ++i)
		cout << apex[i].x << " " << apex[i].y << " ";
}


unique_ptr<Figure> Rectangle::clone() const {
	Point points[4];
	for (int i = 0; i < 4; ++i) {
		points[i].x = apex[i].x;
		points[i].y = apex[i].y;
	}
	return  make_unique<Rectangle>(points);
}

Ellipse::Ellipse() {
	for (int i = 0; i < 4; ++i)
		apex[i].x = apex[i].y = 0;
}

Ellipse::Ellipse(Point* points) {
	for (int i = 0; i < 4; ++i) {
		apex[i] = points[i];
	}
}

float Ellipse::get_perim() {
	float ose[2];
	ose[0] = (this->apex[0].p_len(this->apex[2])) / 2;
	ose[1] = (this->apex[1].p_len(this->apex[3])) / 2;
	return 4 * ((3.14 * ose[0] * ose[1] + ose[0] - ose[1]) / (ose[0] + ose[1]));
}

float Ellipse::get_square() {
	float ose[2];
	ose[0] = (this->apex[0].p_len(this->apex[2])) / 2;
	ose[1] = (this->apex[1].p_len(this->apex[3])) / 2;
	return 3.14 * ose[0] * ose[1];
}

void Ellipse::set_min_framing_rectangle(Point* points) {
	points[0] = { apex[0].x, apex[1].y };
	points[1] = { apex[2].x, apex[1].y };
	points[2] = { apex[2].x, apex[3].y };
	points[3] = { apex[0].x, apex[3].y };
}

bool Ellipse::check_figure() {
	return ((apex[0].y == apex[2].y) && (apex[1].x == apex[3].x) &&
		(apex[0].x < apex[1].x) && (apex[2].x > apex[1].x) && (apex[1].y > apex[0].y) && (apex[3].y < apex[0].y));
}

void Ellipse::print() {
	cout << "ellipse  " << " ";
	for (int i = 0; i < 4; ++i)
		cout << apex[i].x << " " << apex[i].y << " ";
}

unique_ptr<Figure> Ellipse::clone() const {
	Point points[4];
	for (int i = 0; i < 4; ++i) {
		points[i].x = apex[i].x;
		points[i].y = apex[i].y;
	}
	return  make_unique<Ellipse>(points);
}

Trapezoid::Trapezoid() {
	for (int i = 0; i < 4; ++i)
		apex[i].x = apex[i].y = 0;
}

Trapezoid::Trapezoid(Point* points) {
	for (int i = 0; i < 4; ++i) {
		apex[i] = points[i];
	}
}

float Trapezoid::get_perim() {
	float perim = 0;
	for (int i = 0; i < 3; i++) {
		perim += this->apex[i].p_len(this->apex[i + 1]);
	}
	perim += this->apex[3].p_len(this->apex[0]);
	return perim;
}

float Trapezoid::get_square() {
	float a, b, c, d;
	b = this->apex[0].p_len(this->apex[1]);
	d = this->apex[1].p_len(this->apex[2]);
	a = this->apex[2].p_len(this->apex[3]);
	c = this->apex[0].p_len(this->apex[3]);
	return (a + b) / 2 * sqrt(c * c - pow(((a - b) * (a - b) + c * c - d * d) / ((a - b) * 2), 2));
}

void Trapezoid::set_min_framing_rectangle(Point* points) {
	points[0] = { MIN(apex[0].x, apex[3].x), apex[0].y };
	points[1] = { MAX(apex[1].x, apex[2].x), apex[0].y };
	points[2] = { MAX(apex[1].x, apex[2].x), apex[3].y };
	points[3] = { MIN(apex[0].x, apex[3].x), apex[3].y };
}

bool Trapezoid::check_figure() {
	return((apex[0].y == apex[1].y) && (apex[2].y == apex[3].y));
}

void Trapezoid::print() {
	cout << "trapezoid" << " ";
	for (int i = 0; i < 4; ++i)
		cout << apex[i].x << " " << apex[i].y << " ";
}

unique_ptr<Figure> Trapezoid::clone() const {
	Point points[4];
	for (int i = 0; i < 4; ++i) {
		points[i].x = apex[i].x;
		points[i].y = apex[i].y;
	}
	return  make_unique<Trapezoid>(points);
}

FigureList& FigureList::operator=(FigureList rhs) {
	swap(rhs);
	return *this;
}

void FigureList::swap(FigureList& OtherList) noexcept {
	std::swap(this->figure_list, OtherList.figure_list);
}
FigureList::FigureList(const FigureList& OtherList) {
	for (int i = 0; i < size(); ++i) {
		figure_list.push_back(OtherList[i]->clone());
	}
}

void FigureList::delete_figure(int index) {
	auto iter = figure_list.cbegin();
	figure_list.erase(iter + index);
}

int FigureList::size() {

	return figure_list.size();
}

void FigureList::insert(FigurePtr figure, int index) {
	auto iter = figure_list.cbegin();
	figure_list.emplace(iter + index, figure);
}
FigurePtr FigureList::operator[](const int index) const {
	if (index < 0) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	return figure_list[index];
}

void FigureList::add(FigurePtr figure) {
	figure_list.push_back(figure);
}
Figure& FigureList::max_square_search() {
	int j = 0;
	for (int i = 1; i < figure_list.size(); ++i)
		if ((figure_list[j]->get_square()) < (figure_list[i]->get_square()))
			j = i;
	return *figure_list[j];
}

void FigureList::print() {
	for (int i = 0; i < size(); ++i) {
		cout << i << ") ";figure_list[i]->print();
		cout << endl;
	}
}