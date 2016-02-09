#pragma once

#include <iostream>
#include "point.h"

class Noeud
{
public:
	Noeud(const float cout_g, const float cout_h, const float cout_f, std::pair<int, int> parent);
	float cout_g, cout_h, cout_f;
	std::pair<int, int> parent;
};