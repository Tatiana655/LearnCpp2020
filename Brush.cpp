#include "Brush.h"

void Pen::Print(HDC hdc, Field& field, int size, int koef, const Pos& p, const Pos& p2)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);
	int x = p.GetX(), y = p.GetY();
	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hdc, hPen);
	Ellipse(hdc, x - size / 2, y - size / 2, x + size / 2, y + size / 2);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	x = x / koef;
	y = y / koef;
	int size1 = size / koef;

	for (int i = ((y - size1 / 2) > 0 ? (y - size1 / 2) : 0); i < (y + size1 / 2); i++) //уравнение круга
	{
		for (int j = ((x - size1 / 2) > 0 ? x - size1 / 2 : 0); j < x + size1 / 2; j++)
		{
			if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE) && ((x - j) * (x - j) + (y - i) * (y - i) < size1 * size1 / 4))
			{
				field[j][i] = color;
			}
		}
	}
}

void Eraser::Print(HDC hdc, Field& field, int size, int koef, const Pos& p, const Pos& p2)
{
	HBRUSH hBrush;
	int x = p.GetX();
	int y = p.GetY();
	hBrush = CreateSolidBrush(WHITE);
	RECT l = { x - size / 2, y - size / 2, x + size / 2, y + size / 2 };
	FillRect(hdc, &l, hBrush);
	DeleteObject(hBrush);

	x = x / koef;
	y = y / koef;
	int size1 = size / koef;

	for (int i = ((y - size1 / 2) > 0 ? (y - size1 / 2) : 0); i < (y + size1 / 2); i++)
	{
		for (int j = ((x - size1 / 2) > 0 ? x - size1 / 2 : 0); j < x + size1 / 2; j++)
		{
			if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE))
			{
				field[j][i] = color;
			}
		}
	}
}

void Line::Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 )
{
	HPEN hPen = CreatePen(PS_SOLID, size, color);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, p1.GetX(), p1.GetY(), NULL);
	LineTo(hdc, p1.GetX(), p2.GetY());
	DeleteObject(hPen);

	int x1 = p1.GetX(), y1 = p1.GetY(), x2 = p2.GetX(), y2 = p2.GetY();
	x1 = x1 / koef;
	x2 = x2 / koef;
	int size1 = size / koef;
	for (int i = min(x1, x2); i <= max(x1, x2); i++)
	{ 
		int y = y1 + (i - x1) * (y2 - y1) / abs(x2 - x1);
		for (int j = y - size1 / 2; j <= y + size1 / 2; j++)
		{
			if ((i >= 0) && (j >= 0) && (i < W_SIZE) && (j < W_SIZE))
			{
				field[i][j] = color;
			}
		}
	}
}

void Rect:: Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 )
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	RECT l = { p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY() };
	FillRect(hdc, &l, hBrush);
	DeleteObject(hBrush);

	int x1 = p1.GetX()/koef, y1 = p1.GetY()/koef, x2 = p2.GetX()/koef, y2 = p2.GetY()/koef;
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

void Circle:: Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 )
{
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	SelectObject(hdc, hPen);
	Ellipse(hdc, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
	DeleteObject(hBrush);
	DeleteObject(hPen);

	double x1 = p1.GetX()/koef, y1 = p1.GetY() / koef, x2 = p2.GetX() / koef, y2 = p2.GetY() / koef;

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