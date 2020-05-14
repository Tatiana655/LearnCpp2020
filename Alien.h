#pragma once

enum ALIEN_TYPE //mb A1 or A1-3
{
	A_1,
	A_2,
	A_3,
	A_4,
	A_5
};

class Alien : public StdObject
{
	ALIEN_TYPE type;
	int speed;
	
	// printAlien
	// killedAlien?
};
//mb 