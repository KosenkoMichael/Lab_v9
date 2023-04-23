#pragma once
#include<vector>
#include<memory>
#include<iostream>
using namespace std;
namespace kos {
	class Figure;
	using FigurePtr = std::shared_ptr<Figure>;
	struct Point {
		float x;
		float y;
		float p_len(Point point);
	};

	class Figure {
	protected:
		Figure() = default;
	public:
		Point apex[4];
		virtual float get_perim() = 0;
		virtual float get_square() = 0;
		Point* get_points();
		void virtual set_min_framing_rectangle(Point* points) = 0;
		bool operator==(const Figure& rhs);
		bool virtual check_figure() = 0;
		void virtual print() = 0;
		virtual unique_ptr<Figure> clone() const = 0;
	};

	class Rectangle : public Figure {
	public:
		Rectangle();
		Rectangle(Point* points);
		float get_perim() override;
		float get_square() override;
		void set_min_framing_rectangle(Point* points);
		bool check_figure() override;
		void print() override;
		unique_ptr<Figure> clone() const override;
	};
	class Ellipse : public Figure {
	public:
		Ellipse();
		Ellipse(Point* points);
		float get_perim() override;
		float get_square() override;
		void set_min_framing_rectangle(Point* points);
		bool check_figure() override;
		void print() override;
		unique_ptr<Figure> clone() const override;
	};
	class Trapezoid : public Figure {
	public:
		Trapezoid();
		Trapezoid(Point* points);
		float get_perim() override;
		float get_square() override;
		void set_min_framing_rectangle(Point* points);
		bool check_figure() override;
		void print() override;
		unique_ptr<Figure> clone() const override;
	};
	class FigureList {
	private:
		std::vector<FigurePtr> figure_list;
	public:
		void swap(FigureList& OtherList) noexcept;

		FigureList() = default;
		FigureList(const FigureList& OtherList);
		FigurePtr operator[](const int index) const;
		FigureList& operator=(FigureList rhs);

		int size();


		void add(FigurePtr figure);
		void insert(FigurePtr a, int index);
		void delete_figure(int index);
		Figure& max_square_search();
		void print();
	};
};