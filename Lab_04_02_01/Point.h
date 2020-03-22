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
	//add addition at 
	void IncPos(int xi, int yi) { pos.SetX(pos.GetX() + xi); pos.SetY(pos.GetY() + yi); }
	void IncSpeed(int xi, int yi) { speed.SetX(speed.GetX() + xi); speed.SetY(speed.GetY() + yi); }
};

class BlinkPoint
{
	list<MyVector> recPoints;
	MovePoint domPoint;
public:
	MovePoint  GetDomPoint() { return domPoint; }
	list<MyVector> GetList() { return recPoints; }

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