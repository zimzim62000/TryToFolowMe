#ifndef Camera_Zim
#define Camera_Zim

#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"

class Camera : public sf::View 
{
public:
	void folowEntity(Entity* entity);
	sf::Vector2i getPosition();
	void setPosition(const int x, const int y);
private:
	int x, y;
};


#endif Camera_Zim