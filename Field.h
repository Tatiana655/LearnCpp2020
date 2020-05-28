#pragma once
#include "Game.h"
#include <vector>
#include "Alien.h"
#include "Gun.h"
#include <iostream>
#include <fstream>

using namespace std;


class Field
{
	vector<Alien> AllAliens;// 11 x 5 
	Gun gun;
public:
	Field(string filename = "C:\\txt\\2.txt")
	{
		ifstream fin(filename);
		int y;
		int x = 0;
		fin >> y;// level of aliens
		for (int i = 1; i <= 55; i++)
		{
			Pos p(x, y);
			Alien A(p);
			x += ICON_SIZE;
			AllAliens.push_back(A);
			if (i % 11 == 0) { x = 0; y += ICON_SIZE; }
		}
	}

	void PrintField(HDC hdc)
	{
		gun.PrintSomeone(hdc);
		for (auto& a : AllAliens)
		{
			if (a.Alive() == true)
				a.PrintSomeone(hdc);
		}
	}

	Gun GetGun() { return gun; }

	int Update(HDC hdc/*, int r*/);

	//init// read coord from file
	//printField
	//updete gun-click
	//Update// if click for gun// gun has bullet ? check + pos aliens use operator? + check for bullet and alive Aliens
};

