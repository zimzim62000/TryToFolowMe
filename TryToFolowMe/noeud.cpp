#include "noeud.h"

Noeud::Noeud(const float cout_g, const float cout_h, const float cout_f, std::pair<int, int> parent)
{
	this->cout_g = cout_g;
	this->cout_h = cout_h;
	this->cout_f = cout_f;
	this->parent = parent;
}
