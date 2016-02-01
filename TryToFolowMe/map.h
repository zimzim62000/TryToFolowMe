#ifndef Map_Zim
#define Map_Zim

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "entity_manager.h"
#include "case_game.h"
#include <queue>

typedef enum
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	TOP_LEFT = 4,
	TOP_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_RIGHT = 7
}Direction;

class MyMap : public sf::Sprite
{
public:
	MyMap(EntityManager* entityManager);

	void Load(std::string filename);

	virtual void Update(sf::RenderWindow* window);

	int CheckCollision(Entity* entity, Direction direction);

	std::string topArea, bottomArea, leftArea, rightArea;

	~MyMap();

	std::string tileSet;
	int width, height, tileWidth, tileHeight;
	int* data;

	std::pair<int,int> ConvertPosition(const int x, const int y);
	case_game getOnThisPosition(const int x, const int y);
	std::queue<Point*> CalculateParcours(const sf::Vector2f &start, const sf::Vector2i &end, sf::RenderWindow* window);
	case_game getOnThisPositionNoeud(const int x, const int y);
private:
	case_game* getCaseGame(const int value);

	sf::Texture* texture;
	sf::Image* tileSetTexture;
	EntityManager* entityManager;
	std::map<std::pair<int, int>, case_game*> mapEntity;
	case_game* black_case;
	case_game* brun_case;
	case_game* grey_case;
	case_game* white_case;
};

#endif Map_Zim