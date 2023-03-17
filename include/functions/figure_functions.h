#pragma once

namespace kos {
	enum FigureType {
		ellipse,
		trapezoid,
		rectangle
	};
	struct Point {
		float x;
		float y;
		float p_len(Point point);
	};
	class Figure {
	private:
		FigureType type;
		Point apex[4];
	public:
		Figure();
		Figure(FigureType type, Point* points);
		bool operator== (const Figure figure) const;
		FigureType get_type();
		float get_point(char a, int i);
		float get_perim();
		float get_square();
		void set_min_framing_rectangle(Figure figure);
		Figure* create(FigureType type, Point* points);
		void print();
	};
	class FigureList {
	private:
		Figure** figures;
		int _size = 0;
	public:
		~FigureList();
		FigureList();
		Figure* operator[](const int index) const;
		void figure_add(Figure* figure);
		Figure* indexed_get(int index);
		int get_size();
		void figure_insert(Figure* figure, int index);
		void indexed_delete(int index);
		Figure max_square_search();
		void print();
	};
}
