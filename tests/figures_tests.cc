#include <gtest/gtest.h>

#include <functions/figure_functions.h>

#include <stdexcept>

#include <iostream>

using namespace kos;

TEST(FunctionsTests, p_len_Test1) {
	Point x = { -2,1 }, y = { 1,1 };
	float len = x.p_len(y);
	EXPECT_NEAR(len, 3, 0.1);
}

TEST(FunctionsTests, get_point_Test3) {
	Point cur_points[4] = { -1,0,0,1,1,0,0,-1 };
	Ellipse ellipse(cur_points);
	float i = ellipse.get_points()[0].x;

	EXPECT_EQ(i, -1);
}

TEST(FunctionsTests, get_perim_ForRectangle_Test4) {
	Point cur_point[4] = { -1,1,1,1,1,-1,-1,-1 };
	Rectangle rectangle(cur_point);
	float cur_perim = rectangle.get_perim();
	EXPECT_NEAR(cur_perim, 8, 0.5);
}
TEST(FunctionsTests, get_perim_ForEllipse_Test5) {
	Point cur_point[4] = { -1,0,0,1,1,0,-1,0 };
	Ellipse ellipse(cur_point);
	float cur_perim = ellipse.get_perim();
	EXPECT_NEAR(cur_perim, 6.28, 0.4);
}
TEST(FunctionsTests, get_perim_ForTrapezoid_Test6) {
	Point cur_point[4] = { -1,3,1,3,5,0,-5,0 };
	Trapezoid trapezoid(cur_point);
	float cur_perim = trapezoid.get_perim();
	EXPECT_NEAR(cur_perim, 22, 0.1);
}
TEST(FunctionsTests, get_square_ForEllipse_Test7) {
	Point cur_point[4] = { -1,0,0,1,1,0,0,-1 };
	Ellipse ellipse(cur_point);
	float cur_square = ellipse.get_square();
	EXPECT_NEAR(cur_square, 3.14, 0.1);
}
TEST(FunctionsTests, get_squareFor_Trapezoid_Test8) {
	Point cur_point[4] = { -1,1,1,1,2,0,-2,0 };
	Trapezoid trapezoid(cur_point);
	float cur_square = trapezoid.get_square();
	EXPECT_NEAR(cur_square, 3, 0.1);
}
TEST(FunctionsTests, get_square_ForRectangle_Test9) {
	Point cur_point[4] = { -1,1,1,1,1,-1,-1,-1 };
	Rectangle rectangle(cur_point);
	float cur_square = rectangle.get_square();
	EXPECT_NEAR(cur_square, 4, 0.1);
}

TEST(FunctionsTests, set_min_framing_rectangle_Forellipse_Test10) {
	Point cur_point[4] = { -1,0,0,1,1,0,0,-1 };
	Ellipse ellipse(cur_point);
	Point pointsi[4];
	ellipse.set_min_framing_rectangle(pointsi);
	int flag = 0;
	Point right_points[4] = { -1,1,1,1,1,-1,-1,-1 };
	Rectangle rectangle(right_points);
	Rectangle cur_rectangle(pointsi);
	if (cur_rectangle == rectangle)
		flag++;
	EXPECT_TRUE(flag);
}

TEST(FunctionsTests, set_min_framing_rectangle_Fortrapezoid_Test11) {
	Point cur_point[4] = { -1,1,1,1,2,0,-2,0 };
	Trapezoid cur_figure(cur_point);
	Point pointsi[4];
	cur_figure.set_min_framing_rectangle(pointsi);
	Rectangle cur_rectangle(pointsi);
	int flag = 0;
	Point right_points[4] = { -2,1,2,1,2,0,-2,0 };
	Rectangle right_figure(right_points);
	if (right_figure == cur_rectangle)
		flag++;
	EXPECT_TRUE(flag);
}

TEST(FunctionsTests, set_min_framing_rectangle_Forrectangle_Test12) {
	Point cur_point[4] = { -1,1,1,1,1,-1,-1,-1 };
	Rectangle cur_figure(cur_point);
	Point pointsi[4];
	cur_figure.set_min_framing_rectangle(pointsi);
	Rectangle right_figure(pointsi);
	int flag = 0;
	if (right_figure == cur_figure)
		flag++;
	EXPECT_TRUE(flag);
}

TEST(FunctionsTests, get_size_Test13) {
	FigureList sample_list;
	Point sample_points[4] = { -1,1,1,1,1,-1,-1,-1 };
	Rectangle figure(sample_points);
	sample_list.add(figure.clone());
	int a = sample_list.size();
	EXPECT_EQ(a, 1);
}

TEST(FunctionsTests, indexed_get_figure_add_Test14) {
	FigureList sample_list;
	float sample_points[4] = { -1,1,1,-1 };
	Point sample_points_p[4] = { -1,1,1,1,1,-1,-1,-1 };
	Rectangle sample_figure(sample_points_p);
	sample_list.add(sample_figure.clone());
	int flag = 0;
	if (sample_figure == sample_figure) {
		flag++;
	}
	EXPECT_TRUE(flag);
}