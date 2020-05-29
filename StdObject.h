#pragma once

#include "Position.h"
#include "Game.h"
#define BUL_SIZE 2

#define BUL_SPEED 4
using namespace std;


class Bullet
{
	Pos pos;
public:

	Bullet(Pos p)
	{
		pos = p;
	}

	void MoveBullet()
	{
		Pos p(0, BUL_SPEED);
		pos = pos + p;
	}

	void PrintBullet(HDC hdc)
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		int x = pos.GetX();
		int y = pos.GetY();
		RECT l = { x, y, x + BUL_SIZE, y + BUL_SIZE };
		FillRect(hdc, &l, hBrush);
	}

	int check(Pos& p) { return pos.check(p); }

	//print // update
};

class StdObject
{
protected:
	Pos pos;
	vector<Bullet> bullets;
public:
	Pos GetPos() { return pos; }

	void PrintSomeone(HDC hdc);// id or other?

	void UpdateBullets(HDC hdc);

	void SetBullet()
	{
		Bullet b(pos);
		bullets.push_back(b);
	}

	int checkBullets(Pos& p);
};
