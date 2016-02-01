#ifndef MainGame_Zim
#define MainGame_Zim

#pragma once

#include "game_state.h"
#include "map.h"
#include "player.h"

#include <iostream>

class main_game : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(float const dt, sf::RenderWindow* window);
	void Render(float const dt, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	void DebugMode(sf::RenderWindow* window);

	MyMap* map;
	EntityManager* manager;
	Player* player;
	sf::Font* font;
	sf::Text* pausedText;
	
	int selected;
	bool paused, pauseKey, enterKey, debugKey, mouseClickRight, onMouseClickRight;
};

#endif MainGame_Zim