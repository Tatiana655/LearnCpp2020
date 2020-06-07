#pragma once
#pragma once
using namespace std;
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Pos.h"

#define W_SIZE 1000

#define BLACK RGB(0,0,0)
#define GREY RGB(128,128,128)
#define WHITE RGB(255,255,255)
#define RED RGB(255,0,0)
#define ORANGE RGB(255,128,0)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,128)
#define SEA RGB(0,0,255)
#define PURPLE RGB(255,0,255)

//zoom koef
class Brush
{
protected:
	//vector<Pos> vecPos;
	int size = 6;
	int koef = 1;//zoom
	long color = WHITE;
	//+сделать отдельные ашники
	//mb operator++ for size
public:
	virtual void Print(HDC hdc, vector<vector<long>>& field, const Pos& p1, const Pos& p2 = { 0,0 }) = 0;
	void SetColor(long c) { color = c; }
	//change size/
	//if zoom change koef
};


class Pen : public Brush
{
	//Pos pos;
public:
	Pen(long col)
	{
		color = col;
	}
	void Print(HDC hdc, vector<vector<long>>& field, const Pos& p, const Pos& p2 = { 0,0 })
	{
		HBRUSH hBrush = CreateSolidBrush(color);
		SelectObject(hdc, hBrush);
		int x = p.GetX(), y = p.GetY();
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		SelectObject(hdc, hPen);
		Ellipse(hdc, x - size / 2, y - size / 2, x + size / 2, y + size / 2);
		DeleteObject(hBrush);
		DeleteObject(hPen);

		for (int i = ((y - size / 2) > 0 ? (y - size / 2) : 0); i < (y + size / 2); i++) //уравнение круга
		{
			for (int j = ((x - size / 2) > 0 ? x - size / 2 : 0); j < x + size / 2; j++)
			{
				if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE) && ((x - j) * (x - j) + (y - i) * (y - i) < size * size / 4))
				{
					field[j][i] = color;
				}
			}
		}
	}
};

class Eraser : public Brush
{
public:
	void Print(HDC hdc, vector<vector<long>>& field, const Pos& p, const Pos& p2 = { 0,0 })
	{
		HBRUSH hBrush;
		int x = p.GetX();
		int y = p.GetY();
		hBrush = CreateSolidBrush(WHITE);
		RECT l = { x - size / 2, y - size / 2, x + size / 2, y + size / 2 };
		FillRect(hdc, &l, hBrush);
		DeleteObject(hBrush);

		for (int i = ((y - size / 2) > 0 ? (y - size / 2) : 0); i < (y + size / 2); i++)
		{
			for (int j = ((x - size / 2) > 0 ? x - size / 2 : 0); j < x + size / 2; j++)
			{
				if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE))
				{
					field[j][i] = color;
				}
			}
		}
	}
};

class Line : public Brush
{
	//remember
public:
	Line(long col)
	{
		color = col;
	}
	void Print(HDC hdc, vector<vector<long>>& field, const Pos& p1, const Pos& p2 = { 0,0 })
	{
		HPEN hPen = CreatePen(PS_SOLID, size, color);
		SelectObject(hdc, hPen);
		MoveToEx(hdc, p1.GetX(), p1.GetY(), NULL);
		LineTo(hdc, p1.GetX(), p2.GetY());
		DeleteObject(hPen);

		int x1 = p1.GetX(), y1 = p1.GetY(), x2 = p2.GetX(), y2 = p2.GetY();

		for (int i = min(x1, x2); i <= max(x1, x2); i++)
		{
			int y = y1 + (i - x1) * (y2 - y1) / abs(x2 - x1);
			for (int j = y - size / 2; j <= y + size / 2; j++)
			{
				if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE))
				{
					field[i][j] = color;
				}
			}
		}
	}
};

class Rect : public Brush
{
	//remember
public:
	Rect(long col)
	{
		color = col;
	}
	void Print(HDC hdc, vector<vector<long>>& field, const Pos& p1, const Pos& p2 = { 0,0 })
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(color);
		RECT l = { p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY() };
		FillRect(hdc, &l, hBrush);
		DeleteObject(hBrush);

		int x1 = p1.GetX(), y1 = p1.GetY(), x2 = p2.GetX(), y2 = p2.GetY();
		for (int i = min(x1, x2); i <= max(x2, x1); i++)
		{
			for (int j = min(y1, y2); j <= max(y2, y1); j++)
			{
				if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE))
				{
					field[i][j] = color;
				}
			}
		}
	}
};

class Circle : public Brush
{
	//remember
public:
	Circle(long col)
	{
		color = col;
	}
	void Print(HDC hdc, vector<vector<long>>& field, const Pos& p1, const Pos& p2 = { 0,0 })
	{
		HBRUSH hBrush = CreateSolidBrush(color);
		SelectObject(hdc, hBrush);
		HPEN hPen = CreatePen(PS_SOLID, 1, color);
		SelectObject(hdc, hPen);
		Ellipse(hdc, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
		DeleteObject(hBrush);
		DeleteObject(hPen);

		double x1 = p1.GetX(), y1 = p1.GetY(), x2 = p2.GetX(), y2 = p2.GetY();

		for (double i = min(x1, x2); i <= max(x2, x1); i++)
		{
			for (double j = min(y1, y2); j <= max(y2, y1); j++)
			{
				if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE) && (((i - (x1 + x2) / 2) * (i - (x1 + x2) / 2)) / (x1 - x2) / (x1 - x2) + (j - (y1 + y2) / 2) * (j - (y1 + y2) / 2) / (y2 - y1) / (y2 - y1) <= 1))
				{
					field[(int)i][(int)j] = color;
				}
			}
		}
	}
};