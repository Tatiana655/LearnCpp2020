#pragma once
#include <vector>
#include "Alien.h"
#include "Gun.h"
using namespace std;


class Field
{
	vector<vector<Alien>> AllAliens;// 11 x 5 connected
	Gun gun;
public:
	//init// read coord from file
	//printField
	//changeField(time) bullet + Aliens
	//Update// if click for gun
	//check for bullet and alive Aliens
};

