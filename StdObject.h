#pragma once

#include "Position.h"
#include "Game.h"
using namespace std;

class StdObject
{
protected:
	Pos pos;
	int alive;

public:
	Pos GetPos() { return pos; }
	int GetStat() { return alive; }
	//change pos//oper+
	void Death()
	{
		alive = 0;
	}
};