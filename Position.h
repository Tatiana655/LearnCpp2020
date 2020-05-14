#pragma once
class Pos
{
public:
	Pos(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	
	int GetX() { return x; }
	int GetY() { return y; }

	//getter, setter, oper+...
private:
	int x;
	int y;
};

