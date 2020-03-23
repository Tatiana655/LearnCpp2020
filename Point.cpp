#include "stdafx.h"
#include "Point.h"

void Init(BlinkPoint & p)
{
	MovePoint mp;
	MyVector v, v1;
	v.SetX(500);
	v.SetY(500);

	v1.SetX(0);
	v1.SetY(0);

	mp.SetPos(v);
	mp.SetSpeed(v1);
	p.SetDomPoint(mp);
}

void PrintMovePoint(HDC hdc, BlinkPoint p)
{
	HPEN hWhitePen;
	HBRUSH hBlackBrush;
	HGDIOBJ hOldBrush;

	hWhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, hWhitePen);
	hOldBrush = SelectObject(hdc, hBlackBrush);

	//p.IncPos(p.GetSpeed().GetX(), p.GetSpeed().GetY());
	int x = p.GetDomPoint().GetPos().GetX();
	int y = p.GetDomPoint().GetPos().GetY();
	Ellipse(hdc, x, y, x + PSIZE, y + PSIZE);
	p.PrintTrase(hdc);
}