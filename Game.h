#pragma once
#include "framework.h"
#include "Lab4_04_01.h"
#include <string>
#include <stdlib.h>
#include <memory>
#include <vector>
#include "Field.h"
#include "Gun.h"
#include "Alien.h"

using namespace std;

class Game
{
	Field field;
	int score;
public:
	Game(string filename = "C:\\txt\\2.txt")
	{
		score = 0;
		Field f(filename);
		field = f;
	}
	Field Getfield() { return field; }

	int UpdsteG(HDC hdc, int r);

	void ChangelvlField(string filename, HDC hdc)
	{
		Field f(filename);
		field = f;
		f.PrintField(hdc);
	}
};