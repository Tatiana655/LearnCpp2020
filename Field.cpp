#include "Field.h"

int Field :: Update(HDC hdc/*, int r*/)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	RECT l = { 0, 0, FIL_SIZE, FIL_SIZE };
	FillRect(hdc, &l, hBrush);
	FillRect(hdc, &l, hBrush);
	int win = 0;

	gun.PrintSomeone(hdc);

	for (auto& a : AllAliens)
	{
		if (a.Alive())
		{
			win++;
			a.HorizonAlien(hdc);
			if ((a.GetPos().GetX() == 0) || (a.GetPos().GetX() == FIL_SIZE))
				for (auto& i : AllAliens)
					i.InvSpeed();
			if (rand() % 1000 == 3) { a.SetBullet(); }
		}
		else
		{
			if (rand() % 10 == 6)
				a.DownAlien(hdc);
		}

		if (a.checkBullets(gun.GetPos()) == 1)
		{
			if (gun.Death() == -1) return -1;
		}

		if (gun.checkBullets(a.GetPos()) == 1)
		{
			a.Death();
			for (auto& i : AllAliens)
				i.FaterSpeed(2);
			return 1;
		}
	}
	if (win == 0) return 2;
	return 0;
}
