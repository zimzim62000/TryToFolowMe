#ifndef Field_Zim
#define Field_Zim

#pragma once

#include "entity.h"

class Field : public Entity
{
public:
	Field(EntityManager* entityManager, MyMap* map, float x, float y);
	bool Update(float const dt, sf::RenderWindow* window);
private:
	MyMap* map;
	float speed, speedAngle, angle, engine, brakes, speedMax;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	sf::Vector2f direction;
};

#endif Field_Zim