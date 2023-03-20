#include <functions/figure_functions.h>

#include <cmath>
#include<stdexcept>
#include<iostream>

#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) > (y) ? (y) : (x)

using namespace kos;

using namespace std;

float Point::p_len(Point point) {
	return sqrt( pow( this->x - point.x, 2 ) + pow( this->y - point.y , 2 ) );
}

Figure::Figure() {
	this->type = rectangle;
	for (int i = 0; i < 4; i++) {
		this->apex[i] = { 0,0 };
	}
}

Figure::Figure(FigureType type, Point* points) {
	this->type = type;
	for (int i = 0; i < 4; i++) {
		this->apex[i] = points[i];
	}
}

bool Figure::operator== (const Figure figure) const {
	if (this->type != figure.type)
		return false;
	for (int i = 0; i < 4; i++) {
		if ((this->apex[i].x != figure.apex[i].x) || (this->apex[i].y != figure.apex[i].y))
			return false;
	}
	return true;
}

FigureType Figure::get_type() {
	return this->type;
}


float Figure::get_point(char a, int i) {
	switch (a) {
	case 'x': return this->apex[i].x;
	case 'y': return this->apex[i].y;
	}
}

float Figure::get_perim() {
	float perim = 0;
	float ose[2];
	switch(this->type) {
	case ellipse: 
		ose[0] = (this->apex[0].p_len(this->apex[2])) / 2;
		ose[1] = (this->apex[1].p_len(this->apex[3])) / 2;
		return 4 * ((3.14 * ose[0] * ose[1] + ose[0] - ose[1]) / (ose[0] + ose[1]));
	case trapezoid:
		for (int i = 0; i < 3; i++) {
			perim += this->apex[i].p_len(this->apex[i+1]);
		}
		perim += this->apex[3].p_len(this->apex[0]);
		return perim;
	case rectangle:
		for (int i = 0; i < 3; i++) {
			perim += this->apex[i].p_len(this->apex[i + 1]);
		}
		perim += this->apex[3].p_len(this->apex[0]);
		return perim;
	}
}

float Figure::get_square() {
	float ose[2];
	float a, b, c, d;
	switch (this->type) {
	case ellipse:
		ose[0] = (this->apex[0].p_len(this->apex[2])) / 2;
		ose[1] = (this->apex[1].p_len(this->apex[3])) / 2;
		return 3.14 * ose[0] * ose[1];
	case trapezoid:
		b = this->apex[0].p_len(this->apex[1]);
		d = this->apex[1].p_len(this->apex[2]);
		a = this->apex[2].p_len(this->apex[3]);
		c = this->apex[0].p_len(this->apex[3]);
		return (a + b) / 2 * sqrt(c * c - pow(((a - b) * (a - b) + c * c - d * d) / ((a - b) * 2), 2));
	case rectangle:
		return apex[0].p_len(apex[1]) * apex[0].p_len(apex[3]);
	}
}

void Figure::set_min_framing_rectangle(Figure figure) {
	this->type = rectangle;
	switch (figure.type) {
	case ellipse:
		this->apex[0] = {figure.apex[0].x, figure.apex[1].y};
		this->apex[1] = {figure.apex[2].x, figure.apex[1].y};
		this->apex[2] = {figure.apex[2].x, figure.apex[3].y};
		this->apex[3] = {figure.apex[0].x, figure.apex[3].y};
		break;
	case trapezoid:
		this->apex[0] = { MIN(figure.apex[0].x, figure.apex[3].x), figure.apex[0].y};
		this->apex[1] = { MAX(figure.apex[1].x, figure.apex[2].x), figure.apex[0].y };
		this->apex[2] = { MAX(figure.apex[1].x, figure.apex[2].x), figure.apex[3].y };
		this->apex[3] = { MIN(figure.apex[0].x, figure.apex[3].x), figure.apex[3].y };
		break;
	case rectangle:
		for(int i=0; i<4; i++)
		this->apex[i] = figure.apex[i];
		break;
	}
}



Figure* FigureList::operator[](const int index) const{
	if ((index < 0) || (_size <= index)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	return figures[index];
}

int FigureList::get_size() {
	return _size;
}

Figure* FigureList::indexed_get(int index) {
	if ((index < 0) || (_size <= index)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	return this->figures[index];
}

void FigureList::figure_add(Figure* figure) {
	auto copy = new Figure*[_size+1];
	for (int i = 0; i < _size; ++i) {
		copy[i] = figures[i];
	}
	copy[_size] = figure;
	delete[] figures;
	figures = copy;
	this->_size++;
}

void FigureList::figure_insert(Figure* figure, int index) {
	if ((index < 0) || (_size < index)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	auto copy = new Figure * [_size + 1];
	for (int i = 0; i < _size; i++) {
		if (i < index)
			copy[i] = figures[i];
		else
			copy[i + 1] = figures[i];
	}
	copy[index] = figure;
	delete[] figures;
	figures = copy;
	this->_size++;
}

void FigureList::indexed_delete(int index) {
	if ((index < 0) || (index > _size)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	auto copy = new Figure * [_size - 1];
	/*for (int i = index; i < _size-1; i++) {
			figures[i] = figures[i + 1];
	}
	for (int i = index; i < _size - 1; i++) {
		copy[i] = figures[i];
	}*/
	for (int i = 0; i < _size - 1; ++i) {
		if (index > i)
			copy[i] = figures[i];
		else
			copy[i] = figures[i + 1];
	}
	delete[] figures;
	figures = copy;
	this->_size--;
}

Figure FigureList::max_square_search() {
	if (_size == 0) {
		throw out_of_range("[FigureList is empty");
	}
	Figure result_figure(*figures[0]);
	for (int i = 0; i < _size; i++) {
		if (result_figure.get_square() < (* figures[i]).get_square())
			result_figure = *figures[i];
	}
	return result_figure;
}

FigureList::FigureList() {
	figures = new Figure * [0];
	_size = 0;
}

FigureList:: ~FigureList() {
	for (int i = 0; i < _size; ++i) {
		delete figures[i];
	}
	delete[] figures;
}

void FigureList::print(){
	for (int i = 0; i < _size; ++i) {
		cout << i << ") ";
		switch (figures[i]->get_type()) {
		case 0: cout << "ellipse" << " ";
			break;
		case 1: cout << "trapezoid" << " ";
			break;
		case 2: cout << "rectangle" << " ";
			break;
		}
		for (int j = 0; j < 4; ++j) {
			cout << figures[i]->get_point('x', j) << " " << figures[i]->get_point('y', j) << " ";
		}
		cout << "\n";
	}
}

Figure* Figure::create(FigureType type, Point* points) {
	return new Figure(type, points);
}

void Figure::print() {
	switch (type) {
	case 0: cout << "ellipse" << " ";
		break;
	case 1: cout << "trapezoid" << " ";
		break;
	case 2: cout << "rectangle" << " ";
		break;
	}
	for (int j = 0; j < 4; ++j) {
		cout << apex[j].x << " " << apex[j].y << " ";
	}
	cout << "\n";
}
FigureList::FigureList(FigureList& rhs){
	Figure figure;
	Point points[4];
	for (int i = 0; i < rhs._size; ++i) {
		for (int j = 0; j < 4;++j) {
			points[j].x = rhs.figures[i]->get_point('x', j);
			points[j].y = rhs.figures[i]->get_point('y', j);
		}
		figure_add(figure.create(rhs.figures[i]->get_type(), points));
	}
}
void FigureList::swap(FigureList& rhs)noexcept{
	std::swap(_size, rhs._size);
	std::swap(figures, rhs.figures);
}

FigureList& FigureList::operator=(FigureList& rhs) {
	FigureList copy(rhs);
	swap(copy);
	return *this;
}

bool Figure::check_figure() {
	bool flag = false;
	switch (type) {
	case ellipse: {
		if ((apex[0].y == apex[2].y) && (apex[1].x == apex[3].x) &&
			(apex[0].x < apex[1].x) && (apex[2].x > apex[1].x) && (apex[1].y > apex[0].y) && (apex[3].y < apex[0].y))
			flag = true;
	}
				break;
	case trapezoid: {
		if ((apex[0].y == apex[1].y) && (apex[2].y == apex[3].y))
			flag = true;
	}
				  break;
	case rectangle: {
		if ((apex[0].x == apex[3].x) && (apex[1].x == apex[2].x) && (apex[0].y == apex[1].y) && (apex[3].y == apex[2].y) && (apex[0].x < apex[1].x) && (apex[0].y > apex[3].y))
			flag = true;
	}
				  break;
	}
	return flag;
}

Figure* Figure::create_ellipse(float* ellipse_points) {
	type = ellipse;
	apex[0].x = ellipse_points[0];
	apex[0].y = apex[2].y = ellipse_points[1];
	apex[1].x = apex[3].x = ellipse_points[2];
	apex[1].y = ellipse_points[3];
	apex[2].x = apex[1].x * 2 - apex[0].x;
	apex[3].y = apex[0].y * 2 - apex[1].y;
	return new Figure(type, apex);
}
Figure* Figure::create_rectangle(float* rectangle_points) {
	type = rectangle;
	apex[0].x = apex[3].x = rectangle_points[0];
	apex[0].y = apex[1].y = rectangle_points[1];
	apex[1].x = apex[2].x = rectangle_points[2];
	apex[2].y = apex[3].y = rectangle_points[3];
	return new Figure(type, apex);
}
Figure* Figure::create_trapezoid(float* trapezoid_points) {
	type = trapezoid;
	for (int i = 0, j=0; i < 4; ++i) {
		apex[i].x = trapezoid_points[j];
		apex[i].y = trapezoid_points[j+1];
		j += 2;
	}
	return new Figure(type, apex);
}