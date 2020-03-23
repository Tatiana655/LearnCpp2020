#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <sstream>

using namespace std;

#define PSIZE 50

class MyVector
{
public:
	int GetX() { return x; }
	int GetY() { return y; }

	void SetX(int i) { x = i; }
	void SetY(int i) { y = i; }

	//a.operator+(b) == a+b

	MyVector operator+(MyVector b)
	{
		MyVector v;
		v.SetX(this->x + b.x);
		v.SetY(this->y + b.y);
		return v;
	}
private:
	int x;
	int y;
};

class MovePoint
{
	MyVector pos;
	MyVector speed;
public:
	MyVector GetPos() { return pos; }
	MyVector GetSpeed() { return speed; }

	void SetPos(MyVector i) { pos = i; }
	void SetSpeed(MyVector i) { speed = i; }

	void IncPos(MyVector add) { pos = pos.operator+(add); }
	void IncSpeed(MyVector add) { speed = speed.operator+(add); }

};

class BlinkPoint
{
	list<MyVector> recPoints;
	MovePoint domPoint;
public:
	MovePoint  GetDomPoint() { return domPoint; }

	void PrintTrase(HDC hdc)
	{
		int i = 0;
		for (auto &elem : recPoints)
		{
			HPEN hWhitePen;
			HBRUSH hBlackBrush;
			HGDIOBJ hOldBrush;
			int A = 255 - (4 - i) * 51;
			hBlackBrush = CreateSolidBrush(RGB(A, A, A));
			hWhitePen = CreatePen(PS_SOLID, 0, RGB(A, A, A));
			hOldBrush = SelectObject(hdc, hBlackBrush);
			int x = elem.GetX();
			int y = elem.GetY();
			Ellipse(hdc, x, y, x + PSIZE, y + PSIZE);
			i++;
		}
	}

	void SetDomPoint(MovePoint i)
	{
		recPoints.push_front(i.GetPos());
		if (recPoints.size() > 5)
			recPoints.pop_back();
		domPoint = i;
	}

};


void Init(BlinkPoint & p);

void PrintMovePoint(HDC hdc, BlinkPoint p);