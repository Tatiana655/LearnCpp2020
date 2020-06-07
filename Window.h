#pragma once
#pragma once
#include "Brush.h"
#define ICON_SIZE 20
enum class COLOR
{
	black,
	gray,
	white,
	red,
	orange,
	yellow,
	green,
	blue,
	sea,
	purple
};
enum OBJ
{
	PEN,
	ERASER,
	LINE,
	CIRCLE,
	RECTANGLE,
	ZOOM
};
//+/-

class Window
{
private:
	vector<vector<long>> field;
	OBJ obj = PEN;
	long color;
public:
	Window()
	{
		color = BLACK;
		for (int i = 0; i < W_SIZE; i++)
			for (int j = 0; j < W_SIZE; j++)
				field[i][j] = RGB(255, 255, 255);
	}
	void changeStat(Pos& p);
	void PrintSomething(HDC hdc, const Pos& p1, const Pos& p2 = { 0,0 });
}