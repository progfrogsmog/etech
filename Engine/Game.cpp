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
	//R Key resistor
	if (wnd.kbd.KeyIsPressed(0x52) && releasedR)//press R
	{
		releasedR = false;
		if (tempDrawRes)//here R is pressed again while resistor is not placed so turn resistor accordingly
		{
			if (resistorDir > 4)
			{
				resistorDir = 1;
			}
			else
			{
				resistorDir <<= 1;
			}
		}
		else
		{
			resistorDir = 1;
		}
		if (noneSelected)
		{
			tempDrawRes = true;
			noneSelected = false;
		}
	}
	else if(!wnd.kbd.KeyIsPressed(0x52) && !releasedR)//release R
	{
		releasedR = true;
	}
	//L Key line
	if (wnd.kbd.KeyIsPressed(0x4C) && releasedL)//L for line draw
	{
		releasedL = false;
		if (noneSelected)
		{
			tempDrawLine = true;
			noneSelected = false;
		}
	}
	else if (!wnd.kbd.KeyIsPressed(0x4c) && !releasedL)
	{
		releasedL = true;
	}
	//mouse left
	if (wnd.mouse.LeftIsPressed() && releasedMouseLeft)//mouse left button
	{
		releasedMouseLeft = false;
		if (tempDrawRes)
		{
			resistors[amountResistors++] = Resistor("R1", 1000, Vei2(PixToPos(mouseX, 280), PixToPos(mouseY, 30)));
			tempDrawRes = false;
			noneSelected = true;
		}
		if (activeLineDraw)
		{
			lines[amountLines++] = activeRect;
			activeLineDraw = false;
			//noneSelected = true;
		}
		if (tempDrawLine)
		{
			firstPoint = Vei2((mouseX - 280) / 40, (mouseY - 30) / 40);
			if (board.GetPoint(firstPoint).IsFree())
			{
				activeLineDraw = true;
				tempDrawLine = false;
			}
		}
	}
	else if (!wnd.mouse.LeftIsPressed() && !releasedMouseLeft)
	{
		releasedMouseLeft = true;
	}
	//mouse right
	if (wnd.mouse.RightIsPressed() && releasedMouseRight)
	{
		tempDrawRes = false;
		tempDrawLine = false;
		noneSelected = true;
		activeLineDraw = false;
		releasedMouseRight = false;
	}
	else if (!wnd.mouse.RightIsPressed() && !releasedMouseRight)
	{
		releasedMouseRight = true;
	}
	//drag/extract Line
	if (activeLineDraw)
	{
		//calc difference
		distX = (280 + 40 * firstPoint.x) - mouseX;
		if (distX < 0)
		{
			distX = -distX;
			negX = false;
		}
		else
		{
			negX = true;
		}
		distY = (30 + 40 * firstPoint.y) - mouseY;
		if (distY < 0)
		{
			distY = -distY;
			negY = false;
		}
		else
		{
			negY = true;
		}
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

	if (tempDrawRes)
	{
		if (resistorDir & 0b1)
		{
			gfx.DrawRect(mouseX - 5, mouseY, 10, 120, Colors::Black);//res
			gfx.DrawRect(mouseX - 15, mouseY + 20, 30, 80, Colors::Blue);//res
		}
		else if (resistorDir & 0b10)
		{
			gfx.DrawRect(mouseX , mouseY - 5, 120, 10, Colors::Black);//res
			gfx.DrawRect(mouseX + 20, mouseY - 15, 80, 30, Colors::Blue);//res
		}
		else if (resistorDir & 0b100)
		{
			gfx.DrawRect(mouseX - 5, mouseY - 120, 10, 120, Colors::Black);//res
			gfx.DrawRect(mouseX - 15, mouseY - 100, 30, 80, Colors::Blue);//res
		}
		else
		{
			gfx.DrawRect(mouseX - 120, mouseY - 5, 120, 10, Colors::Black);//res
			gfx.DrawRect(mouseX - 100, mouseY - 15, 80, 30, Colors::Blue);//res
		}
	}
	//choose point
	if (tempDrawLine)
	{
		if(!activeLineDraw)
			gfx.DrawRect(mouseX - 12, mouseY - 12, 24, 24, Colors::Gray);//soldering iron in future?
	}
	//drag line
	if (activeLineDraw)
	{
		if(negX && negY)
		{
			if (distX >= distY)
			{
				gfx.DrawRect(mouseX, 30 + firstPoint.y * 40 - 4, distX, 8, Colors::Gray);
				activeRect = { mouseX, mouseX + distX, 30 + firstPoint.y * 40 - 4, 30 + firstPoint.y * 40 - 4 + 8 };
			}
			else
			{
				gfx.DrawRect(280 + firstPoint.x * 40 - 4, mouseY, 8, distY, Colors::Gray);
				activeRect = { 280 + firstPoint.x * 40 - 4, 280 + firstPoint.x * 40 - 4 + 8, mouseY, distY + mouseY };
			}
		}
		else if(negX)
		{
			if (distX >= distY)
			{
				gfx.DrawRect(mouseX, 30 + firstPoint.y * 40 - 4, distX, 8, Colors::Gray);
				activeRect = { mouseX, mouseX + distX, 30 + firstPoint.y * 40 - 4, 30 + firstPoint.y * 40 - 4 + 8 };
			}
			else
			{
				gfx.DrawRect(280 + firstPoint.x * 40 - 4, 30 + firstPoint.y * 40, 8, distY, Colors::Gray);
				activeRect = { 280 + firstPoint.x * 40 - 4, 280 + firstPoint.x * 40 - 4 + 8, 30 + firstPoint.y * 40, 30 + firstPoint.y * 40 + distY };
			}
		}
		else if(negY)
		{
			if (distX >= distY)
			{
				gfx.DrawRect(280 + firstPoint.x * 40, 30 + firstPoint.y * 40 - 4, distX, 8, Colors::Gray);
				activeRect = { 280 + firstPoint.x * 40, 280 + firstPoint.x * 40 + distX, 30 + firstPoint.y * 40 - 4, 30 + firstPoint.y * 40 - 4 + 8 };
			}
			else
			{
				gfx.DrawRect(280 + firstPoint.x * 40 - 4, mouseY, 8, distY, Colors::Gray);
				activeRect = { 280 + firstPoint.x * 40 - 4, 280 + firstPoint.x * 40 - 4 + 8, mouseY, mouseY + distY };
			}
		}
		else
		{
			if (distX >= distY)
			{
				gfx.DrawRect(280 + firstPoint.x * 40, 30 + firstPoint.y * 40 - 4, distX, 8, Colors::Gray);
				activeRect = { 280 + firstPoint.x * 40, 280 + firstPoint.x * 40 + distX, 30 + firstPoint.y * 40 - 4, 30 + firstPoint.y * 40 - 4 + 8 };
			}
			else
			{
				gfx.DrawRect(280 + firstPoint.x * 40 - 4, 30 + firstPoint.y * 40, 8, distY, Colors::Gray);
				activeRect = { 280 + firstPoint.x * 40 - 4, 280 + firstPoint.x * 40 - 4 + 8, 30 + firstPoint.y * 40, 30 + firstPoint.y * 40 + distY };
			}
		}
	}
	for (int i = 0; i < amountLines; i++)
	{
		gfx.DrawRect(lines[i].left, lines[i].top, lines[i].GetWidth(), lines[i].GetHeight(), Colors::Gray);
	}
}