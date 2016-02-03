#include <iostream>
#include <fstream>
#include <sstream>

#include "map.h"
#include "Utility.h"
#include "path_finding.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"



using namespace rapidjson;

MyMap::MyMap(EntityManager* entityManager)
{
	this->texture = new sf::Texture();
	this->tileSetTexture = new sf::Image();
	this->entityManager = entityManager;

	this->width = 0;
	this->height = 0;
	this->tileWidth = 0;
	this->tileHeight = 0;
}

void MyMap::Load(std::string filename)
{
	std::ifstream mapFile("Graphics/Maps/" + filename);
	std::string mapFileData((std::istreambuf_iterator<char>(mapFile)),
	std::istreambuf_iterator<char>());
	Document mapFileDoc;
	mapFileDoc.Parse(mapFileData.c_str());

	this->width = mapFileDoc["width"].GetInt();
	this->height = mapFileDoc["height"].GetInt();
	this->tileWidth = mapFileDoc["tilewidth"].GetInt();
	this->tileHeight = mapFileDoc["tileheight"].GetInt();

	Value& dataArray = mapFileDoc["layers"];

	/* map case*/
	Value& tilesets = mapFileDoc["tilesets"];
	Value& properties = tilesets[0]["tileproperties"];
	
	Value& blackcase = properties["0"];
	this->black_case = new case_game(std::stoi(blackcase["passable"].GetString()), std::stoi(blackcase["weight"].GetString()));
	Value& bruncase = tilesets[0]["tileproperties"]["1"];
	this->brun_case = new case_game(std::stoi(bruncase["passable"].GetString()), std::stoi(bruncase["weight"].GetString()));
	Value& greycase = tilesets[0]["tileproperties"]["2"];
	this->grey_case = new case_game(std::stoi(greycase["passable"].GetString()), std::stoi(greycase["weight"].GetString()));
	Value& whitecase = tilesets[0]["tileproperties"]["3"];
	this->white_case = new case_game(std::stoi(whitecase["passable"].GetString()), std::stoi(whitecase["weight"].GetString()));
	
	this->data = new int[this->width * this->height];

	if (dataArray.IsArray())
	{
		for (int i = 0; i < dataArray.Capacity(); i += 1)
		{
			this->tileSet = dataArray[i]["name"].GetString();
			Value& dataTileset = dataArray[i]["data"];

			for (int y = 0; y < this->height; y += 1)
			{
				for (int x = 0; x < this->width; x += 1)
				{
					int tmp = dataTileset[x + y * this->width].GetInt();
					this->data[x + y * this->width] = tmp;
					this->mapEntity[std::pair<int, int>(x, y)] = this->getCaseGame(tmp);
				}
			}
		}
	}

	this->texture->create(this->width * this->tileWidth, this->height * this->tileHeight);

	this->tileSetTexture->loadFromFile("Graphics/Tilesets/" + this->tileSet);

	sf::Image tileWhite, tileGrey, tileBurn, tileBlack;

	tileWhite.create(32, 32);
	tileGrey.create(32, 32);
	tileBurn.create(32, 32);
	tileBlack.create(32, 32);

	tileBlack.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth, this->tileHeight), true);
	tileBurn.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth, 0, this->tileWidth, this->tileHeight), true);
	tileGrey.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, this->tileHeight, this->tileWidth, this->tileHeight), true);
	tileWhite.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth, this->tileHeight, this->tileWidth, this->tileHeight), true);


	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			switch (this->data[x + y *  this->width])
			{
			case 1:
				this->texture->update(tileBlack, x * this->tileWidth, y * this->tileHeight);
				break;
			case 2:
				this->texture->update(tileBurn, x * this->tileWidth, y * this->tileHeight);
				break;
			case 3:
				this->texture->update(tileGrey, x * this->tileWidth, y * this->tileHeight);
				break;
			case 4:
				this->texture->update(tileWhite, x * this->tileWidth, y * this->tileHeight);
				break;
			default:
				break;
			}
		}
	}

	this->setTexture(*this->texture);
}

void MyMap::Update(sf::RenderWindow* window)
{
}

int MyMap::CheckCollision(Entity* entity, Direction direction)
{
	int x = (int)(entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileWidth;
	int y = (int)(entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileHeight;
	switch (direction)
	{
	case LEFT:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileHeight;
		break;
	case RIGHT:
		x = (int)(entity->getPosition().x) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileHeight;
		break;
	case UP:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileWidth;
		y = (int)(entity->getPosition().y) / this->tileHeight;
		break;
	case DOWN:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height) / this->tileHeight;
		break;
	case TOP_LEFT:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width) / this->tileWidth;
		y = (int)(entity->getPosition().y) / this->tileHeight;
		break;
	case TOP_RIGHT:
		x = (int)(entity->getPosition().x) / this->tileWidth;
		y = (int)(entity->getPosition().y) / this->tileHeight;
		break;
	case BOTTOM_LEFT:
		x = (int)(entity->getPosition().x + entity->getGlobalBounds().width) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height) / this->tileHeight;
		break;
	case BOTTOM_RIGHT:
		x = (int)(entity->getPosition().x) / this->tileWidth;
		y = (int)(entity->getPosition().y + entity->getGlobalBounds().height) / this->tileHeight;
		break;
	}
	return this->data[x + y * this->width];
}


MyMap::~MyMap()
{
	delete this->texture;
	delete this->tileSetTexture;
	delete this->data;
	this->mapEntity.clear();
}

std::pair<int, int> MyMap::ConvertPosition(const int x, const int y, const float zoom)
{
	return std::pair<int, int>(int(x / this->tileWidth), int(y / this->tileWidth));
}

case_game MyMap::getOnThisPosition(const int x, const int y, const float zoom) {
	return *this->mapEntity[std::pair<int, int>(int(x / this->tileWidth), int(y / this->tileWidth))];
}

case_game MyMap::getOnThisPositionNoeud(const int x, const int y) {
	return *this->mapEntity[std::pair<int, int>(int(x), int(y))];
}

case_game* MyMap::getCaseGame(const int value) {
	switch (value) {
	case 1:
		return this->black_case;
		break;
	case 2:
		return this->brun_case;
		break;
	case 3:
		return this->grey_case;
		break;
	case 4:
		return this->white_case;
		break;
	default:
		break;
	}
}

std::queue<Point*>  MyMap::CalculateParcours(const sf::Vector2f &start, const sf::Vector2i &end, sf::RenderWindow* window, const float zoom)
{
	bool find = false;
	std::queue<Point*> targets;

	int start_x = abs(start.x/this->tileWidth);
	int start_y = abs(start.y /this->tileHeight);

	int end_x = abs(end.x / this->tileWidth);
	int end_y = abs(end.y / this->tileHeight);

	if(start_x != end_x || start_y != end_y){
		PathFinding MyPathFinding;
		sf::Clock deltaTime;
		MyPathFinding.findRoad(this, window, start_x, start_y, end_x, end_y);
		if(MyPathFinding.chemin.size() != 0){
			std::cout << deltaTime.restart().asSeconds() << std::endl;
			while(MyPathFinding.chemin.size() > 0) {
				targets.push(new Point(MyPathFinding.chemin.front().x*this->tileWidth, MyPathFinding.chemin.front().y*this->tileWidth));
				MyPathFinding.chemin.pop_front();
			}
		}/*
		else {
			targets.push(new Point(start_x*this->tileWidth, start_y*this->tileWidth));
		}*/
	}
	return targets;
}