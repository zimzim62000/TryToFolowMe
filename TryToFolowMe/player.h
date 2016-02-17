#ifndef Player_Zim
#define Player_Zim

#pragma once

#include "entity.h"

const float PI = 3.1415f;

class Player : public Entity
{
public:
	Player(EntityManager* entityManager, MyMap* map, float x, float y, float speed);
	bool Update(float const dt, sf::RenderWindow* window);
private:
	MyMap* map;
	float speed, speedAngle, angle, engine, brakes, speedMax;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	sf::Vector2f direction;
};
#endif Player_Zim