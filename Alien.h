#pragma once
#include "Game.h"
#include "StdObject.h"
#define A_SPEED 3

//enum ALIEN_TYPE //mb A1 or A1-3
//{
//	A_1,
//	A_2,
//	A_3,
//	A_4,
//	A_5
//};

class Alien : public StdObject
{
	//ALIEN_TYPE type;
	bool alive;
	int speed;
public:
	Alien(Pos& p)
	{
		pos = p;
		alive = true;
		speed = 2;
		//type = t;
	}

	bool Alive() { return alive; }

	void Death() { alive = false; }
	
	void FaterSpeed(int d) { speed += d; }

	void InvSpeed() { speed = -speed; }

	void HorizonAlien(HDC hdc)
	{
		Pos p(speed);
		pos = pos + p;
		PrintSomeone(hdc);
	}

	void DownAlien(HDC hdc)
	{
		Pos p(0, ICON_SIZE);
		pos = pos + p;
		PrintSomeone(hdc);
	}
};
