#include "Window.h"

void Window::PrintRect(HDC hdc, long color, int x1, int y1, int x2, int y2)
{
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	HPEN hPen = CreatePen(PS_SOLID, 2, BLACK);
	SelectObject(hdc, hPen);
	RECT l = { x1, y1, x2, y2 };
	FillRect(hdc, &l, hBrush);
	DeleteObject(hBrush);
	DeleteObject(hPen);
}

void Window::PrintField(HDC hdc)
{
	for (int i = 0; i < W_SIZE; i++)
	{
		for (int j = 0; j < W_SIZE; j++)
		{
			if (koef == 1)
				SetPixel(hdc, i, j, field[i][j]);
			else
			{
				PrintRect(hdc, field[i][j], i * koef - koef / 2, j * koef - koef / 2, i * koef + koef / 2, j * koef + koef / 2);
			}
		}
	}
}
//if in window // no checks // print and remember
void Window::PrintSomething(HDC hdc, const Pos& p1)
{
	switch (obj)
	{
	case PEN:
	{
		Pen pen(color);
		pen.Print(hdc, field, size, koef, p1);
	}
	break;
	case ERASER:
	{
		Eraser er;
		er.Print(hdc, field, size, koef, p1);
	}
	break;
	case LINE:
	{
		Line l(color);
		l.Print(hdc, field, size, koef, buf, p1);
	}
	break;
	case CIRCLE:
	{
		Circle circ(color);
		circ.Print(hdc, field, size, koef, buf, p1);
	}
	break;
	case RECTANGLE:
	{
		Rect r(color);
		r.Print(hdc, field, size, koef, buf, p1);
	}
	break;
	default:
		break;
	}
}

//change color or brush// if out window// with checks
void Window::changeStat(HDC hdc, Pos& p)
{
	int x = p.GetX(), y = p.GetY();
	string s = sys.Change(x, y, hdc);

	if (s.compare("BLACK") == 0) color = BLACK;
	else
		if (s.compare("GREY") == 0) color = GREY;
		else
			if (s.compare("WHITE") == 0) color = WHITE;
			else
				if (s.compare("RED") == 0) color = RED;
				else
					if (s.compare("ORANGE") == 0) color = ORANGE;
					else
						if (s.compare("YELLOW") == 0) color = YELLOW;
						else
							if (s.compare("GREEN") == 0) color = GREEN;
							else
								if (s.compare("BLUE") == 0) color = BLUE;
								else
									if (s.compare("SEA") == 0) color = SEA;
									else
										if (s.compare("PURPLE") == 0) color = PURPLE;
										else
											if (s.compare("PEN") == 0) obj = PEN;
											else
												if (s.compare("ERASER") == 0) obj = ERASER;
												else
													if (s.compare("LINE") == 0) obj = LINE;
													else
														if (s.compare("CIRCLE") == 0) obj = CIRCLE;
														else
															if (s.compare("RECTANGLE") == 0) obj = RECTANGLE;
															else
																if (s.compare("ZOOM_IN") == 0) {
																	size *= 2;
																	koef *= 2;
																	PrintWindow(hdc);
																	PrintField(hdc);
																}
																else
																	if (s.compare("ZOOM_OUT") == 0) {
																		if (koef != 1)
																		{
																			size /= 2;
																			koef /= 2;
																		}
																		PrintWindow(hdc);
																		PrintField(hdc);
																	}
																	else
																		if (s.compare("SIZE+") == 0) size += 2 * koef;
																		else
																			if (s.compare("SIZE-") == 0) if (size > 0) size -= 2 * koef;

}

void Window::PrintWindow(HDC hdc)
{
	//основное окно
	PrintRect(hdc, WHITE, 0, 0, W_SIZE * koef, W_SIZE * koef);
	//цветные прямоугольники с меню
	vector<long> colors = { BLACK, GREY, WHITE, RED, ORANGE, YELLOW, GREEN, BLUE,  SEA, PURPLE };
	int i = 0;
	for (auto c : colors)
	{
		PrintRect(hdc, c, W_SIZE * koef, i * ICON_SIZE, (W_SIZE + ICON_SIZE) * koef, ((i + 1) * ICON_SIZE) * koef);
		i++;
	}
	for (i = 10; i < 19; i++)
	{
		string s = "";
		if (i == 10) s = "PEN";
		if (i == 11) s = "ERASER";
		if (i == 12) s = "Line";
		if (i == 13) s = "O";
		if (i == 14) s = "RECT";
		if (i == 15) s = "Z_IN";
		if (i == 16) s = "Z_OUT";
		if (i == 17) s = "+";
		if (i == 18) s = "-";
		TextOutA(hdc, W_SIZE * koef, ((i)*ICON_SIZE) * koef, s.c_str(), s.size());
	}
}
void Window::clear()
{
	Field f(W_SIZE, vector<long>(W_SIZE, WHITE));
	field = f;
}

bool Window::Paint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		if ((wParam & MK_LBUTTON))
		{
			HDC hdc = GetDC(hWnd);
			POINT lpPoint;
			Pos p;
			GetCursorPos(&lpPoint);
			p.SetX(LOWORD(lParam)); //узнаём координаты
			p.SetY(HIWORD(lParam));
			PrintSomething(hdc, p);
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		//получить клик, проверить статус и границы клика, если надо то сохрани клик и жди следующего, потом рисуй с заменой статуса.
		Pos p;
		p.SetX(LOWORD(lParam)); //узнаём координаты
		p.SetY(HIWORD(lParam));

		if (p.InWind())
		{
			if (obj == LINE || obj == CIRCLE || obj == RECTANGLE)
			{
				if (buf.emp())
					buf = p;
				else
				{
					PrintSomething(hdc, p);
					buf = { -1,-1 };
				}
			}
			else
			{
				PrintSomething(hdc, p);
			}
		}
		else
			changeStat(hdc, p);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			return 0;
		}
		break;
		}
	}
	break;
	}
	return 1;
}

void Window::Save(string filename)
{
	ofstream out;          // поток для записи
	out.open(filename); // окрываем файл для записи
	if (out.is_open())
	{
		//out << "Hello World!" << std::endl;

		for (auto fvec : field)
		{
			for (auto ind : fvec)
			{
				out << ind << " ";
			}
			out << endl;
		}
	}
	out.close();
}

void Window::Open(HDC hdc, string filename)
{
	int n = W_SIZE;
	ifstream in(filename);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) in >> field[i][j];
	in.close();
	PrintWindow(hdc);
	PrintField(hdc);
}