#include "camera.h"

void Camera::folowEntity(Entity* entity) {
	float a, b;
	this->setPosition(entity->getPosition().x + entity->getGlobalBounds().width / 2, entity->getPosition().y + entity->getGlobalBounds().height / 2);
	a = this->x - this->getSize().x / 2;
	b = this->y - this->getSize().y / 2;
	if (a < 0)a = 0;
	if (b < 0)b = 0;
	this->reset(sf::FloatRect(a, b, this->getSize().x, this->getSize().y));
}

sf::Vector2i Camera::getPosition() {
	return sf::Vector2i(this->x, this->y);
}

void Camera::setPosition(const int x, const int y)
{
	this->x = x;
	this->y = y;
}