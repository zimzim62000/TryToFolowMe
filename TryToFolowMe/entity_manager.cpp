#pragma once

#include "entity_manager.h"

EntityManager::EntityManager(){}

void EntityManager::Add(std::string name, Entity* entity)
{
	std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
	if(found !=  this->entities.end()){
		name += "0";
		found = this->entities.find(name);
	}
	entity->setName(name);
	entity->setOnScene(true);
	this->entities.insert(std::make_pair(name, entity));
}

bool EntityManager::Update(float const dt, sf::RenderWindow* window){
	for(auto& iterator : this->entities){
		iterator.second->Update(dt, window);
	}
	return true;
}

Entity* EntityManager::Get(std::string name)
{
	std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
	
	if (found == this->entities.end())
	{
		return NULL;
	}
	else
	{
		return found->second;
	}
}



void EntityManager::Render(float const dt, sf::RenderWindow* window){
	for(auto& iterator : this->entities){
		window->draw(*iterator.second);
	}
}

Entity* EntityManager::GetAtThisPosition(const int x, const int y, const int tileWidth, const int tileHeight)
{
	for (auto& iterator : this->entities) {
		sf::Vector2f position = iterator.second->getPosition();
		if (abs(position.x / tileWidth) == abs(x/tileWidth) && abs(position.y / tileHeight) == abs(y / tileHeight)) {
			return iterator.second;
		}
	}
	return new Entity();
}