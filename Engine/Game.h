/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Resistor.h"
#include "Rect.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	int CalcCoord(int x_in, int offset = 0);//for fixed points
	int PixToPos(int x_in, int offset = 0);//calc from coord to pos
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Color color = Colors::Cyan;
	int mouseX = 100;
	int mouseY = 100;
	Board board;
	bool releasedR = true;
	bool releasedL = true;
	bool releasedMouseLeft = true;
	bool releasedMouseRight = true;
	bool noneSelected = true;
	bool tempDrawRes = false;
	bool tempDrawLine = false;
	bool activeLineDraw = false;
	int distX, distY;
	bool negX = false, negY = false;
	int amountResistors = 0;
	int amountLines = 0;
	char resistorDir = 0;
	Vei2 firstPoint;
	RectI activeRect;
	Resistor* resistors = new Resistor[50];
	RectI* lines = new RectI[50];
	/********************************/
};