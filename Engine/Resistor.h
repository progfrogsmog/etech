#pragma once
#include "Graphics.h"
#include "Vec2.h"

class Resistor
{
public:
	Resistor() = default;
	Resistor(const std::string& name, int value, const Vei2& pos);
	void Draw(Graphics& gfx);
private:
	std::string name = "XXX";
	int value = 0;
	Vei2 pos = Vei2(0,0);//point connected position
	char dir = 0;
};