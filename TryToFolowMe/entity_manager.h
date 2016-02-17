#ifndef EntityManager_Zim
#define EntityManager_Zim

#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "entity.h"

class EntityManager
{
public:
	EntityManager();
	void Add(std::string name, Entity* entity);
	bool Update(float const dt, sf::RenderWindow* window);
	void Render(float const dt, sf::RenderWindow* window);
	Entity* Get(std::string name);
	Entity* GetAtThisPosition(const int x, const int y, const int tileWidth, const int tileHeight);
private:
	std::unordered_map<std::string, Entity*> entities;
	int numberId;
};

#endif EntityManager_Zim