#pragma once
//#include "framework.h"
//#include "Lab_3_04_02.h"
#include "Wind.h"
void Rect::PrintRect(HDC hdc)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(c.GetR(), c.GetG(), c.GetB()));
	RECT l = { x[0], y[0], x[1], y[1] };
	FillRect(hdc, &l, hBrush);
	TextOutA(hdc, x[0] + abs(x[1] - x[0]) / 4, y[1] - 10, name.c_str(), name.size());
}

void Menu::AddOpt(string name)
{
	vector<int> vy;
	if (opt.empty()) vy = mBase.GetY();
	else vy = (opt[opt.size() - 1]).GetY();
	vy[0] = vy[0] + abs(vy[0] - vy[1]);
	vy[1] = vy[1] + abs(vy[1] - vy[0]);
	Color c = mBase.GetColor();
	Rect(name, c, mBase.GetX(), vy);
}

void WindowMenu::PrintWindow(HDC hdc)
{
	wBase.PrintRect(hdc);
	for (auto w : menu)
	{
		w.PrintMenu(hdc);
	}
	for (auto w : but)
	{
		w.PrintBut(hdc);
	}
}

string WindowMenu::Change(int cx, int cy, HDC hdc)// return string button
{
	for (auto w : but)
	{
		if (w.check(cx, cy) == true) { w.PrintHigthBut(hdc); return w.GetBBase().GetName(); }
	}

	for (auto w : menu)
	{

		if (w.check(cx, cy) == true) { w.PrintOpt(hdc); return w.GetMBase().GetName(); }
	}
	return "";
}

string System::Change(int cx, int cy, HDC hdc)
{
	for (auto u : w)
	{
		if (u.check(cx, cy))
			return u.Change(cx, cy, hdc);
	}
	return "";
}

void System::Init(string filename)
{
	string buff;
	vector<WindowMenu> BW;
	ifstream fin(filename);
	fin >> buff;
	if (buff == "Start")
	{
		while (buff != "End")
		{
			fin >> buff;
			if (buff == "WindowBegin")
			{
				string name;

				vector<int> x, y;
				Color c;
				Rect r;
				fin >> r;//r.FileRect(fin);
				WindowMenu Wind(r);
				while (buff != "WindowEnd")
				{
					fin >> buff;
					if (buff == "ButtonBegin")
					{
						Rect r;
						Color c;
						fin >> r;//r.FileRect(fin);
						while (buff != "ButtonEnd")
						{
							int t;

							fin >> buff;
							if (buff == "HightLight") fin >> c;//{ fin >> t; c.SetR(t); fin >> t; c.SetG(t); fin >> t; c.SetB(t); }


						}
						Button button(r, c);
						Wind.AddButton(button);
					}
					if (buff == "MenuBegin")
					{
						Rect r;
						fin >> r;// r.FileRect(fin);
						Menu m(r);
						while (buff != "MenuEnd")
						{
							string t;
							fin >> buff;
							if (buff == "Options") { fin >> t; m.AddOpt(t); }
						}
						Wind.AddMenu(m);
					}

				}
				w.push_back(Wind);
			}
		}
	}
}

string System::AllSys(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	string s = "";
	HDC hdc = GetDC(hWnd);
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);

		int x = LOWORD(lParam); //узнаём координаты
		int y = HIWORD(lParam);

		s = Change(x, y, hdc);
		return s;
	}
	break;
	case WM_LBUTTONUP:
	{
		HDC hdc = GetDC(hWnd);
		PrintSystem(hdc);
	}
	break;
	}
	return s;
}
