#ifndef Enemy_Zim
#define Enemy_Zim

#pragma once

#include "entity.h"

class Enemy : public Entity
{
public:
	Enemy(EntityManager* entityManager, MyMap* map, float x, float y, float speed);
	bool Update(float const dt, sf::RenderWindow* window);
	void Collision(Entity* entity);
	~Enemy();
private:
	MyMap* map;
	float speed, speedAngle, angle, engine, brakes, speedMax;
	EntityManager* entityManager;
	bool spaceKey, xKey;
	sf::Vector2f direction;
};

#endif Enemy_Zim