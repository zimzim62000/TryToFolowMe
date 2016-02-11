#include "main_game.h"
#include "player.h"
#include "Utility.h"

#include <iostream>

Player::Player(EntityManager* entityManager, MyMap* map, float x, float y, float speed) : Entity(speed)
{
	this->Load("player2-0.png");
	this->setPosition(x, y);
	this->map = map;
	this->groupId = 1;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->angle = 0;
	this->setOrigin(0, 0);

	this->SetNewAnimation("player2-0.png"); 
	this->SetNewAnimation("player2-1.png");
	this->SetNewAnimation("player2-2.png");
	this->SetNewAnimation("player2-3.png");

	this->SetNewRightAnimation("player-right-0.png");
	this->SetNewRightAnimation("player-right-1.png");
	this->SetNewRightAnimation("player-right-2.png");
	this->SetNewRightAnimation("player-right-3.png");

	this->animateMax = 40;
}

bool Player::Update(float const dt, sf::RenderWindow* window)
{
	this->AnimateMe();

	this->MoveOnTarget(dt);

	Entity::Update(dt, window);
	
	return true;
}


void Player::Collision(Entity* entity)
{
	
}

Player::~Player()
{
	delete this->map;
	delete this->entityManager;
	Entity::~Entity();
}