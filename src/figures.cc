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

void Figure::set_type(FigureType Type) {
	this->type = Type;
}

FigureType Figure::get_type() {
	return this->type;
}

void Figure::set_apex(Point* apex){
	for (int i = 0; i < 4; i++) {
		this->apex[i] = apex[i];
	}
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



Figure FigureList::operator[](const int index) const{
	if ((index < 0) || (capacity <= index)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	return figures[index];
}

int FigureList::get_count() {
	return count;
}

Figure FigureList::indexed_get(int index) {
	if ((index < 0) || (capacity <= index)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	return this->figures[index];
}

void FigureList::figure_add(Figure figure) {
	if (count+1>=capacity) {
		throw out_of_range("[FigureList::operator[]] Array is full.");
	}
	Figure void_figure;
	this->figures[count] = figure;
	this->count++;
}

void FigureList::figure_insert(Figure figure, int index) {
	if ((index < 0) || (index>count)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	if (count + 1 > capacity) {
		throw out_of_range("Array is full");
	}
	for (int i = count; i > index; i--) {
		this->figures[i] = this->figures[i - 1];
	}
	this->figures[index] = figure;
	this->count++;
}

void FigureList::indexed_delete(int index) {
	if ((index < 0) || (index > count)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	for (int i = index; i < count; i++) {
		this->figures[i] = this->figures[i+1];
	}
	this->count--;
}

Figure FigureList::max_square_search() {
	if (count == 0) {
		throw out_of_range("[FigureList is empty");
	}
	Figure result_figure;
	for (int i = 0; i < count; i++) {
		if (result_figure.get_square() < this->figures[i].get_square())
			result_figure = this->figures[i];
	}
	return result_figure;
}
