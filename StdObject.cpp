#include "StdObject.h"

void StdObject :: PrintSomeone(HDC hdc)// id?
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	int x = pos.GetX();
	int y = pos.GetY();
	/*RECT l = { x - ICON_SIZE, y - ICON_SIZE, x + ICON_SIZE, y + ICON_SIZE };
	FillRect(hdc, &l, hBrush);*/

	hBrush = CreateSolidBrush(RGB(200, 0, 0));
	RECT l = { x, y, x + ICON_SIZE, y + ICON_SIZE };
	FillRect(hdc, &l, hBrush);

	UpdateBullets(hdc);

}

void StdObject::UpdateBullets(HDC hdc)
{
	for (auto& b : bullets)
	{
		b.MoveBullet();
		b.PrintBullet(hdc);
	}
}

int StdObject::checkBullets(Pos& p)
{
	//for (auto b : bullets)
	vector<Bullet>::iterator it = bullets.begin();
	while (it != bullets.end())
	{
		if (it->check(p) == 1)
		{
			it = bullets.erase(it);
			return 1;
		}
		else
			++it;
	}
	return 0;
}
