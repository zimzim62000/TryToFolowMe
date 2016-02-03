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