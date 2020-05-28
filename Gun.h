#pragma once
#include "Game.h"
#include "Field.h"
#include <memory>
#include "StdObject.h"
#define GUN_SPEED 3
#define FIL_SIZE 500
//enum DIRECTION
//{
//	LEFT,
//	RIGHTT
//};



class Gun : public StdObject
{
	int lives;
public:

	Gun(Pos p = { FIL_SIZE / 2, FIL_SIZE })
	{
		pos = p;
		lives = 3;
	}

	int Death() { lives--; if (lives == 0) return -1; return 1; }

	void AddLive() { lives++; }

	void Right(HDC hdc)
	{
		Pos p(GUN_SPEED);
		pos = pos + p;
		PrintSomeone(hdc);
	}

	void Left(HDC hdc)
	{
		Pos p(-GUN_SPEED);
		pos = pos + p;
		PrintSomeone(hdc);
	}

	//update
	//chsnge pos using speed 
	//print gun 
	//print bullet
};