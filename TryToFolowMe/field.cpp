#include "main_game.h"
#include "field.h"
#include "Utility.h"
#include "config.h"

#include <iostream>


Field::Field(EntityManager* entityManager, MyMap* map, float x, float y) : Entity()
{
	this->Load("field.png");
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

bool Field::Update(float const dt, sf::RenderWindow* window)
{
	Entity::Update(dt, window);

	return true;
}