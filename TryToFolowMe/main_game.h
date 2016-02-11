#ifndef MainGame_Zim
#define MainGame_Zim

#pragma once

#include "game_state.h"
#include "map.h"
#include "player.h"
#include "camera.h"

#include <iostream>

class main_game : public tiny_state
{
public:
	void Initialize(sf::RenderWindow* window);
	void Update(float const dt, sf::RenderWindow* window);
	void Render(float const dt, sf::RenderWindow* window);
	void Destroy(sf::RenderWindow* window);
private:
	void CatchUserAction(sf::RenderWindow* window);

	Camera* camera;
	MyMap* map;
	EntityManager* manager;
	Player* player;
	Entity* ActiveEntity;
	sf::Font* font;
	sf::Text* pausedText;
	
	int selected;
	bool paused, pauseKey, enterKey, debugKey, mouseClickRight, onMouseClickRight, entityActive;
	int zoom;
	float currentZoom;
};

#endif MainGame_Zim