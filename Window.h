#pragma once

#include "Brush.h"
const int ICON_SIZE = 20;

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
	Field field;
	OBJ obj = PEN;
	long color;
public:
//вынести в cpp(!) функции
	//check click change +\- //who is active? where click/s? then print and remrmber(Brush method or here?)
	Window()
	{
		color = BLACK;
		for (int i = 0; i < W_SIZE; i++)
			for (int j = 0; j < W_SIZE; j++)
				field[i][j] = RGB(255, 255, 255);
	}

	OBJ const GetObj() { return obj; }

	//if in window 
	void PrintSomething(HDC hdc, const Pos& p1, const Pos& p2 = { 0,0 })
	{
		switch (obj)
		{
		case PEN:
		{
			Pen pen(color);
			pen.Print(hdc, field, p1);
		}
		break;
		case ERASER:
		{
			Eraser er;
			er.Print(hdc, field, p1);
		}
		break;
		case LINE:
		{
			Line l(color);
			l.Print(hdc, field, p1, p2);
		}
		break;
		case CIRCLE:
		{
			Circle circ(color);
			circ.Print(hdc, field, p1, p2);
		}
		break;
		case RECTANGLE:
		{
			Rect r(color);
			r.Print(hdc, field, p1, p2);
		}
		break;
		default:
			break;
		}
	}
	
	//change color or brush
	
	void changeStat(Pos& p)
	{
		int x = p.GetX(), y = p.GetY();
		if (x <= W_SIZE + ICON_SIZE)
		{
			int num = y / ICON_SIZE;
			switch (num)
			{
			case 0:
				color = BLACK;
				break;
			case 1:
				color = GREY;
				break;
			case 2:
				color = WHITE;
				break;
			case 3:
				color = RED;
				break;
			case 4:
				color = ORANGE;
				break;
			case 5:
				color = YELLOW;
				break;
			case 6:
				color = GREEN;
				break;
			case 7:
				color = BLUE;
				break;
			case 8:
				color = SEA;
				break;
			case 9:
				color = PURPLE;
				break;
			case 10:
				obj = PEN;
				break;
			case 11:
				obj = ERASER;
				break;
			case 12:
				obj = LINE;
				break;
			case 13:
				obj = CIRCLE;
				break;
			case 14:
				obj = RECTANGLE;
				break;
			case 15:
				obj = ZOOM;
				break;
			case 16:
				//size ++// mb parametr for func// unclear yet// mb a few brush and change all // ptr??
				break;
			default:
				break;
			}
		}
	}

};
