#pragma once
#include "Game.h"
//#define FIL_SIZE 500
#define ICON_SIZE 10
class Pos
{
	int x;
	int y;
public:
	Pos(int nx = 0, int ny = 0)
	{
		x = nx;
		y = ny;
	}

	int GetX() { return x; }
	int GetY() { return y; }
	void SetX(int nx) { x = nx; }
	void SetY(int ny) { y = ny; }

	Pos operator+(Pos b)
	{
		Pos v;
		v.SetX(this->x + b.x);
		v.SetY(this->y + b.y);
		return v;
	}

	int check(Pos p)
	{
		int cx = p.GetX();
		int cy = p.GetY();
		if ((cx <= x <= cx + ICON_SIZE) && (cy <= y <= cy + ICON_SIZE)) return 1;
		return 0;
	}
};

