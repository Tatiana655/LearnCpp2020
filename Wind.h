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

	void SetR(int red) { r = red; }
	void SetG(int green) { g = green; }
	void SetB(int blue) { b = blue; }

	int GetR() { return r; }
	int GetG() { return g; }
	int GetB() { return b; }
};

class Rect
{
	string name;
	vector<int> x;
	vector<int> y;
	Color c;

public:
	Rect(string sname = "", Color color = { 255,255,255 }, vector<int> vx = {}, vector<int> vy = {})
	{
		c = color;
		name = sname;
		x = vx;
		y = vy;
	}

	void FileRect(istream& fin)
	{
		string buff;
		string t;
		for (int i = 0; i < 3; i++)
		{
			fin >> buff;
			if (buff == "Name") { fin >> name; }
			if (buff == "Position")
			{
				fin >> t;
				x.push_back(stoi(t));
				fin >> t;
				x.push_back(stoi(t));
				fin >> t;
				y.push_back(stoi(t));
				fin >> t;
				y.push_back(stoi(t));
			}
			if (buff == "Color") { fin >> t; c.SetR(stoi(t)); fin >> t; c.SetG(stoi(t)); fin >> t; c.SetB(stoi(t)); }
		}
	}
	Color GetColor() { return c; }
	vector<int> GetX() { return x; }
	vector<int> GetY() { return y; }
	void SetColor(Color color) { c = color; }

	//print rect
	void PrintRect(HDC hdc)
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(c.GetR(), c.GetG(), c.GetB()));
		RECT l = { x[0], y[0], x[1], y[1] };
		FillRect(hdc, &l, hBrush);
		TextOutA(hdc, x[0] + abs(x[1] - x[0]) / 4, y[1]-10, name.c_str(), name.size());
	}
};

class Button
{
	Rect bBase;
	Rect hLight;
public:
	vector<int> GetX() { return bBase.GetX(); }
	vector<int> GetY() { return bBase.GetY(); }

	Button(Rect rect, Color hightlight = { 0, 0, 0 })
	{
		bBase = rect;
		hLight = rect;
		hLight.SetColor(hightlight);
	}
	void PrintBut(HDC hdc)
	{
		bBase.PrintRect(hdc);
	}
	void PrintHigthBut(HDC hdc)
	{
		hLight.PrintRect(hdc);
	}
};

class Menu
{
	Rect mBase;
	vector<Rect> opt;
public:
	vector<int> GetX() { return mBase.GetX(); }
	vector<int> GetY() { return mBase.GetY(); }
	Menu(Rect rect)
	{
		mBase = rect;
		opt = {};
	}
	void AddOpt(string name)
	{
		vector<int> vy;
		if (opt.empty()) vy = mBase.GetY();
		else vy = (opt[opt.size() - 1]).GetY();
		vy[0] = vy[0] + abs(vy[0] - vy[1]);
		vy[1] = vy[1] + abs(vy[1] - vy[0]);
		Color c = mBase.GetColor();
		Rect(name, c, mBase.GetX(), vy);
	}
	//print menu
	void PrintMenu(HDC hdc)
	{
		mBase.PrintRect(hdc);
	}
	void PrintOpt(HDC hdc)
	{
		for (auto w : opt)
		{
			w.PrintRect(hdc);
		}
	}
};

class Window
{
	Rect wBase;
	vector<Menu> menu;
	vector<Button> but;
public:
	vector<int> GetY() { return wBase.GetY(); }
	vector<int> GetX() { return wBase.GetX(); }
	Window(Rect rect)
	{
		wBase = rect;
		menu = {};
		but = {};
	}
	void AddMenu(Menu m) { menu.push_back(m); }
	void AddButton(Button b) { but.push_back(b); }

	void PrintWindow(HDC hdc)
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
	void Change(int cx, int cy, HDC hdc)
	{
		for (auto w : but)
		{
			vector<int> x = w.GetX();
			vector<int> y = w.GetY();
			if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0])))
			{
				w.PrintHigthBut(hdc);
			}
		}

		for (auto w : menu)
		{
			vector<int> x = w.GetX();
			vector<int> y = w.GetY();
			if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0])))
			{
				w.PrintOpt(hdc);
			}
		}
	}
};

class System
{
	vector<Window> w;
public:
	void Change(int cx, int cy, HDC hdc)
	{
		for (auto u : w)
		{
			vector<int> x = u.GetX();
			vector<int> y = u.GetY();
			if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0]))) u.Change(cx, cy, hdc);
		}
	}
	void PrintSystem(HDC hdc)
	{
		for (auto u : w)
		{
			u.PrintWindow(hdc);
		}
	}

	void Init(string filename)
	{
		string buff;
		vector<Window> BW;
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
					r.FileRect(fin);
					Window Wind(r);
					while (buff != "WindowEnd")
					{
						fin >> buff;
						if (buff == "ButtonBegin")
						{
							Rect r;
							Color c;
							r.FileRect(fin);
							while (buff != "ButtonEnd")
							{
								int t;

								fin >> buff;
								if (buff == "HightLight") { fin >> t; c.SetR(t); fin >> t; c.SetG(t); fin >> t; c.SetB(t); }


							}
							Button button(r, c);
							Wind.AddButton(button);
						}
						if (buff == "MenuBegin")
						{
							Rect r;
							r.FileRect(fin);
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
};