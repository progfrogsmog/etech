/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	board.Init();
}

void Game::Go()
{
	//gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	mouseX = CalcCoord(wnd.mouse.GetPosX(),10);//10 offset to fill the gap between sideboard and board
	mouseY = CalcCoord(wnd.mouse.GetPosY());

	if (wnd.kbd.KeyIsPressed(0x52) && releasedR)
	{
		releasedR = false;
		tempDraw = true;
	}
	else if(!wnd.kbd.KeyIsPressed(0x52) && !releasedR)
	{
		releasedR = true;
	}

	if (wnd.mouse.LeftIsPressed() && tempDraw)
	{
		tempDraw = false;
		resistors[amountResistors++] = Resistor("R1", 1000, Vei2(PixToPos(mouseX,280), PixToPos(mouseY,30)));
	}
}

int Game::CalcCoord(int x_in, int offset)//choose closest point
{
	int i = 0;
	for (; 30 + 40 * i < x_in; i++);
	int less = offset + 30 + 40 * (i-1);
	int more = offset + 30 + 40 * i;
	if (more - x_in < x_in - less)
	{
		return more;
	}
	return less;
}

int Game::PixToPos(int x_in, int offset)
{
	return (x_in - offset) / 40;
}

void Game::ComposeFrame()
{
	gfx.DrawRect(0, 0, 250, gfx.ScreenHeight, Colors::MakeRGB(128, 128, 128));//sideboard
	gfx.DrawRect(10, 10, 230, gfx.ScreenHeight-20, Colors::MakeRGB(64, 64, 64));//sideboard
	board.Draw(gfx);

	for (int i = 0; i < amountResistors; i++)
	{
		resistors[i].Draw(gfx);
	}

	if (tempDraw)
	{
		gfx.DrawRect(mouseX - 5, mouseY, 10, 120, Colors::Black);//res
		gfx.DrawRect(mouseX - 15, mouseY + 20, 30, 80, Colors::Blue);//res
	}
}