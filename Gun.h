#pragma once

#include <memory>
#include "StdObject.h"

enum DIRECTION
{
	LEFT,
	RIGHTT
};

class Bullet
{
	Pos pos;
	int speed;
public:
	//print // update
};

class Gun : public StdObject
{
	DIRECTION dir;
	Bullet bullet;
	int lives;
public:
	//update
	//print gun 
	//print bullet
	//getBullet
};