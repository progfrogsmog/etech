#pragma once
#include "Vec2.h"
#include "Graphics.h"
class Board
{
private:
	class Point
	{
	public:
		void SetPos(int x_in, int y_in);
		Vei2 GetPos() const;
		bool IsFree() const;
	private:
		Vei2 pos;
		int voltage = 0;
		bool free = true; /*for wire*/
		char openDir = 0; /*bitwise information about open direction*/
	};
public:
	void Draw(Graphics& gfx);
	void Init();
	Point GetPoint(Vei2& point);
private:
	Point* points = new Point[600]; /*stores information on the heap*/
};