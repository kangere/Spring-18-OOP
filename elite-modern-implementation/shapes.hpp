#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "graphics.hpp"


class Shape{

public:
	virtual void draw() = 0;
};

class Triangle : public Shape {

private:
	int x1,y1,x2,y2,x3,y3,col;
	BITMAP* gfx_screen;

public:
	Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int col, BITMAP* gfx_screen):
	x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), col(col), gfx_screen(gfx_screen)
	{}

	void draw();

};

class Rectangle : public Shape{
private:
	int tx, ty, bx, by,col;
	BITMAP* gfx_screen;

public:
	Rectangle(int tx, int ty, int bx, int by, int col, BITMAP* gfx_screen):
	tx(tx), ty(ty), bx(bx), by(by), col(col), gfx_screen(gfx_screen)
	{}

	void draw();
};

class Circle : public Shape{
private:
	int cx, cy, radius, col;
	BITMAP* gfx_screen;

public:
	Circle(int cx, int cy, int radius, int colour, BITMAP* gfx_screen):
	cx(cx), cy(cy), radius(radius), col(colour), gfx_screen(gfx_screen)
	{}

	void draw_aa_circle();
	void draw();
	void draw_filled();	
};



#endif