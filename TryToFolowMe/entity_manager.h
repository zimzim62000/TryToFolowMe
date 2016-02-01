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
	Entity* EntityManager::Get(std::string name);
private:
	std::unordered_map<std::string, Entity*> entities;
};

#endif EntityManager_Zim