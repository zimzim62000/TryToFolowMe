#include "main_game.h"
#include "enemy.h"
#include "Utility.h"
#include "config.h"

#include <iostream>


Enemy::Enemy(EntityManager* entityManager, MyMap* map, float x, float y, float speed) : Entity(speed)
{
	this->Load("enemy.png");
	this->setPosition(x, y);
	this->map = map;
	this->groupId = 1;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->angle = 0;
	this->setOrigin(0, 0);
	this->IsONScene = true;
}

bool Enemy::Update(float const dt, sf::RenderWindow* window)
{
	this->MoveOnTarget(dt);

	Entity::Update(dt, window);

	return true;
}


void Enemy::Collision(Entity* entity)
{

}

Enemy::~Enemy()
{
	Entity::~Entity();
}