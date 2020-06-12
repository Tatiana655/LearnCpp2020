#pragma once

const int W_SIZE = 1000;

class Pos
{

	int x;
	int y;
public:	
	bool emp() { if (x == -1 || y == -1) return true; return false; }
	int GetX() const { return x; };
	int GetY() const { return y; };

	void SetX(int cx) { x = cx; };
	void SetY(int cy) { y = cy; };

	Pos(int cx = -1, int cy = -1)
	{
		x = cx;
		y = cy;
	}
	Pos operator+(Pos b)
	{
		Pos v;
		v.SetX(this->x + b.x);
		v.SetY(this->y + b.y);
		return v;
	}
	bool InWind()
	{
		if (x < W_SIZE && (y < W_SIZE)) return true;
		return false;
	}

};

