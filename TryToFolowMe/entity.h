#ifndef Entity_Zim
#define Entity_Zim

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include "entity.h"
#include "point.h"

class Entity : public sf::Sprite
{
public:
	sf::Vector2f velocity;

	Entity();

	Entity(const float speed);

	void Load(std::string filename);

	virtual bool Update(float const dt, sf::RenderWindow* window);

	bool CheckCollision(Entity* entity);

	virtual void Collision(Entity* entity);

	int GroupID();

	int Active();

	void Destroy();

	void AddTarget(const int x, const int y);

	~Entity();

	bool getBusy();

	bool getOnMovement();
	void setName(std::string name);
	std::string getName();

protected:
	void MoveOnTarget(float const dt);

	int active;
	int groupId;
	bool busy, onMove;
	float speed;
	std::string name;
private:
	sf::Texture* texture;
	std::queue<Point*> target;
};

#endif Entity_Zim
