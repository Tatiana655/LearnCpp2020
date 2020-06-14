#pragma once
using namespace std;
#include <Windows.h>
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

class Rect
{
	string name;
	vector<int> x;
	vector<int> y;
	Color c;

public:
	friend istream& operator>> (istream& fin, Rect& r);

	Rect(string sname = "", Color color = { 255,255,255 }, vector<int> vx = {}, vector<int> vy = {})
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

istream& operator>> (istream& fin, Rect& r)
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
	Rect bBase;
	Rect hLight;
public:

	Rect GetBBase() { return bBase; }

	Button(Rect rect, Color hightlight = { 0, 0, 0 })
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
	Rect mBase;
	vector<Rect> opt;
public:
	Rect GetMBase() { return mBase; }

	Menu(Rect rect) { mBase = rect; opt = {}; }

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
	Rect wBase;
	vector<Menu> menu;
	vector<Button> but;
public:

	Rect GetWBase() { return wBase; }

	WindowMenu(Rect rect) { wBase = rect; menu = {}; but = {}; }

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

	string AllSys(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

