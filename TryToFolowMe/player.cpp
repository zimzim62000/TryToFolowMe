#include "main_game.h"
#include "player.h"
#include "Utility.h"

#include <iostream>

Player::Player(EntityManager* entityManager, MyMap* map, float x, float y, float speed) : Entity(speed)
{
	this->Load("player.png");
	this->setPosition(x, y);
	this->map = map;
	this->groupId = 1;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->angle = 0;
	this->setOrigin(0, 0);
}

bool Player::Update(float const dt, sf::RenderWindow* window)
{
	this->MoveOnTarget(dt);
	
	
	sf::View view = window->getView();
	float a, b;
	a = this->getPosition().x + this->getGlobalBounds().width / 2 - view.getSize().x / 2;
	b = this->getPosition().y + this->getGlobalBounds().height / 2 - view.getSize().y / 2;
	if (a < 0)a = 0;
	if (b < 0)b = 0;
	view.reset(FloatRect(a,b, view.getSize().x, view.getSize().y));
	window->setView(view);
	

	Entity::Update(dt, window);

	// réactivation de la vue par défaut
	//window->setView(window->getDefaultView());
	
	return true;
}


void Player::Collision(Entity* entity)
{
	
}