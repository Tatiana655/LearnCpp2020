#include "Game.h"
int Game::UpdsteG(HDC hdc, int r)//r??? return gun??
{
	Gun gun = field.GetGun();
	if (r == 1) gun.Right(hdc); //mb something else (3 x if)
	if (r == -1) gun.Left(hdc);
	if (r == 2) gun.SetBullet();
	gun.PrintSomeone(hdc);
	int k = field.Update(hdc);
	if (k == -1)//game over
	{
		return -1;
	}
	if (k == 2)// next lvl
	{
		field.GetGun().AddLive();
		return 2;
	}
	score += k;
	string  str = "Score";
	string s = to_string(score);
	str += s;
	TextOutA(hdc, 0, FIL_SIZE + 10, str.c_str(), str.size());
	return 0;
}