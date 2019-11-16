#include "Board.h"

void Board::Draw(Graphics& gfx)
{
	gfx.DrawRect(250, 0, gfx.ScreenWidth - 250, gfx.ScreenHeight, Colors::MakeRGB(140, 70, 0));
	for (int y = 25; y < gfx.ScreenHeight - 10; y += 40)
	{
		for (int i = 275; i < gfx.ScreenWidth - 10; i += 40)
		{
			gfx.DrawRect(i, y, 10, 10, Colors::LightGray);
		}
	}
}

void Board::Init()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			points[y * 30 + x].SetPos(25 + 5 + x * 40, 25 + 5 + y * 40);
		}
	}
}

Vei2 Board::GetPointPos(int point)
{
	return points[point].GetPos();
}

void Board::Point::SetPos(int x_in, int y_in)
{
	pos = { x_in,y_in };
}

Vei2 Board::Point::GetPos()//this returns unexpected result
{
	return pos;
}
