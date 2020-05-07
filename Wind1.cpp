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

void Window::PrintWindow(HDC hdc)
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

void Window::Change(int cx, int cy, HDC hdc)
{
	for (auto w : but)
	{
		vector<int> x = w.GetBBase().GetX();
		vector<int> y = w.GetBBase().GetY();
		if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0])))
		{
			w.PrintHigthBut(hdc);
		}
	}

	for (auto w : menu)
	{
		vector<int> x = w.GetMBase().GetX();
		vector<int> y = w.GetMBase().GetY();
		if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0])))
		{
			w.PrintOpt(hdc);
		}
	}
}

void System::Change(int cx, int cy, HDC hdc)
{
	for (auto u : w)
	{
		vector<int> x = u.GetWBase().GetX();
		vector<int> y = u.GetWBase().GetY();
		if (((x[0] <= cx <= x[1]) || (x[1] <= cx <= x[0])) && ((y[0] <= cy <= y[1]) || (y[1] <= cy <= y[0]))) u.Change(cx, cy, hdc);
	}
}

void System::Init(string filename)
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
				fin >> r;//r.FileRect(fin);
				Window Wind(r);
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