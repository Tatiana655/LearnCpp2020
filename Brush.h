#pragma once
using namespace std;
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Pos.h"

using Field = vector<vector<long> > ;

const long BLACK  = RGB(0, 0, 0);
const long GREY   = RGB(128, 128, 128);
const long WHITE  = RGB(255, 255, 255);
const long RED    = RGB(255, 0, 0);
const long ORANGE = RGB(255, 128, 0);
const long YELLOW = RGB(255, 255, 0);
const long GREEN  = RGB(0, 255, 0);
const long BLUE   = RGB(0, 0, 128);
const long SEA    = RGB(0, 0, 255);
const long PURPLE = RGB(255, 0, 255);

class Brush
{
protected:
	//vector<Pos> vecPos;
	//int size = 6;
	//int koef = 1;//zoom
	long color = WHITE;

public:
	virtual void Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 = { 0,0 }) = 0;
	void SetColor(long c) { color = c; }
	
	//void ChangeSize(int delt) { size += delt; }
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
	void Print(HDC hdc, Field& field, int size, int koef, const Pos& p, const Pos& p2 = { 0,0 });
};

class Eraser : public Brush
{
public:
	void Print(HDC hdc, Field& field, int size, int koef, const Pos& p, const Pos& p2 = { 0,0 });
};

class Line : public Brush
{
	//remember
public:
	Line(long col)
	{
		color = col;
	}
	void Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 = { 0,0 });
};

class Rect : public Brush
{
	//remember
public:
	Rect(long col)
	{
		color = col;
	}
	void Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 = { 0,0 });
};

class Circle : public Brush
{
	//remember
public:
	Circle(long col)
	{
		color = col;
	}
	void Print(HDC hdc, Field& field, int size, int koef, const Pos& p1, const Pos& p2 = { 0,0 });
};