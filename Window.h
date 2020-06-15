#pragma once
#include <fstream>
#include "Brush.h"
#include "Wind.h"
const int ICON_SIZE = 20;

enum OBJ
{
	PEN,
	ERASER,
	LINE,
	CIRCLE,
	RECTANGLE,
	ZOOM_IN,
	ZOOM_OUT,
	PLUS,
	MINUS
};

class Window
{
private:
	Field field;
	OBJ obj = PEN;// using for clicks 
	Brush* object;
	int size = 6;
	int koef = 1;
	Pos buf;
	long color;
	System sys;

	void SetBuf(Pos p) { buf = p; }
	Pos  GetBuf() { return buf; }

	void SetColor(long col) { color = col; };
	void PrintRect(HDC hdc, long color, int x1, int y1, int x2, int y2);

	void PrintField(HDC hdc);

	void changeStat(HDC hdc, Pos& p);
public:
	Window()
	{
		Field f(W_SIZE, vector<long>(W_SIZE, WHITE));
		color = BLACK;
		field = f;
		object = new Pen(color);
	}

	~Window()
	{
		delete object;
	}

	void clear();

	bool Paint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Save(string filename);

	void Open(HDC hdc, string filename);
};
