#pragma once

class Pos
{

	int x;
	int y;
public:
	int GetX() const { return x; };
	int GetY() const { return y; };

	void SetX(int cx) { x = cx; };
	void SetY(int cy) { y = cy; };

	Pos(int cx, int cy)
	{
		x = cx;
		y = cy;
	}
};

