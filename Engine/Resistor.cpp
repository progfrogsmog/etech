#include "Resistor.h"

Resistor::Resistor(const std::string& name, int value, const Vei2& pos)
	:
	name(name),
	value(value),
	pos(pos)
{}

void Resistor::Draw(Graphics & gfx)
{
	gfx.DrawRect(280 + 40 * pos.x - 5 , 30 + 40 * pos.y     , 10, 120, Colors::Black);//wire
	gfx.DrawRect(280 + 40 * pos.x - 15, 30 + 40 * pos.y + 20, 30, 80 , Colors::Blue);//body
}
