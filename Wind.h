#pragma once
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <wingdi.h>

class Color
{
	int r;
	int g;
	int b;
public:

	Color(int cr = 0, int cg = 0, int cb = 0)
	{
		r = cr;
		g = cg;
		b = cb;
	}

	int GetR() { return r; }
	int GetG() { return g; }
	int GetB() { return b; }
	friend istream& operator>> (istream& fin, Color& c);
};

istream& operator>> (istream& fin, Color& c)
{
	fin >> c.r;
	fin >> c.g;
	fin >> c.b;
	return fin;
}

class Rectw
{
	string name;
	vector<int> x;
	vector<int> y;
	Color c;

public:
	friend istream& operator>> (istream& fin, Rectw& r);

	Rectw(string sname = "", Color color = { 255,255,255 }, vector<int> vx = {}, vector<int> vy = {})
	{
		c = color;
		name = sname;
		x = vx;
		y = vy;
	}

	string GetName() { return name; }

	Color GetColor() { return c; }

	vector<int> GetX() { return x; }

	vector<int> GetY() { return y; }

	void SetColor(Color color) { c = color; }

	void PrintRect(HDC hdc);
};

istream& operator>> (istream& fin, Rectw& r)
{
	string buff;
	int t;

	fin >> buff;
	if (buff == "Name") { fin >> r.name; }
	fin >> buff;
	if (buff == "Position")
	{
		fin >> t;
		r.x.push_back(t);
		fin >> t;
		r.x.push_back(t);
		fin >> t;
		r.y.push_back(t);
		fin >> t;
		r.y.push_back(t);
	}
	fin >> buff;
	if (buff == "Color") fin >> r.c;//{ fin >> t; c.SetR(stoi(t)); fin >> t; c.SetG(stoi(t)); fin >> t; c.SetB(stoi(t)); }

	return fin;
}

class Button
{
	Rectw bBase;
	Rectw hLight;
public:

	Rectw GetBBase() { return bBase; }

	Button(Rectw rect, Color hightlight = { 0, 0, 0 })
	{
		bBase = rect;
		hLight = rect;
		hLight.SetColor(hightlight);
	}

	bool check(int cx, int cy)
	{
		vector<int> x = bBase.GetX();
		vector<int> y = bBase.GetY();
		if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0])))
		{
			return true;
		}
		return false;
	}
	void PrintBut(HDC hdc) { bBase.PrintRect(hdc); }
	void PrintHigthBut(HDC hdc) { hLight.PrintRect(hdc); }
};

class Menu
{
	Rectw mBase;
	vector<Rectw> opt;
public:
	Rectw GetMBase() { return mBase; }

	Menu(Rectw rect) { mBase = rect; opt = {}; }

	void AddOpt(string name);

	void PrintMenu(HDC hdc) { mBase.PrintRect(hdc); }

	void PrintOpt(HDC hdc) { for (auto w : opt) w.PrintRect(hdc); }

	bool check(int cx, int cy)
	{
		vector<int> x = mBase.GetX();
		vector<int> y = mBase.GetY();
		if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0])))
		{
			return true;
		}
		return false;
	}

};

class WindowMenu
{
	Rectw wBase;
	vector<Menu> menu;
	vector<Button> but;
public:

	Rectw GetWBase() { return wBase; }

	WindowMenu(Rectw rect) { wBase = rect; menu = {}; but = {}; }

	void AddMenu(Menu m) { menu.push_back(m); }

	void AddButton(Button b) { but.push_back(b); }

	void PrintWindow(HDC hdc);

	string Change(int cx, int cy, HDC hdc);

	bool check(int cx, int cy)
	{
		vector<int> x = wBase.GetX();
		vector<int> y = wBase.GetY();
		if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0]))) return true;
		return false;
	}
};

class System
{
	vector<WindowMenu> w;
public:
	string Change(int cx, int cy, HDC hdc);

	void PrintSystem(HDC hdc) { for (auto u : w) u.PrintWindow(hdc); }

	void Init(string filename);

	string AllSys(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
};

void Rectw::PrintRect(HDC hdc)
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
	Rectw(name, c, mBase.GetX(), vy);
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
		if(u.check(cx,cy))
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
				Rectw r;
				fin >> r;//r.FileRect(fin);
				WindowMenu Wind(r);
				while (buff != "WindowEnd")
				{
					fin >> buff;
					if (buff == "ButtonBegin")
					{
						Rectw r;
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
						Rectw r;
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