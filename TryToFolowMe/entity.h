#ifndef Entity_Zim
#define Entity_Zim

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
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
	void setOnScene(const bool enable);
	bool getOnScene();

protected:
	void MoveOnTarget(float const dt);
	void AnimateMe(const float dt);
	void SetNewAnimation(std::string nameAnimation);
	void SetNewRightAnimation(std::string nameAnimation);
	void SetNewLeftAnimation(std::string nameAnimation);

	int active, groupId;
	bool busy, onMove, IsAnimate, IsONScene;
	float speed;
	std::string name;

	float animateMax;
	/* Animated none */
	float animateCount;
	int animateKey;
	std::vector<std::string> animated;
	/* Animated Right */
	float animateRightCount;
	int animateRightKey;
	std::vector<std::string> animatedRight;
	/* Animated Left */
	float animateLeftCount;
	int animateLeftKey;
	std::vector<std::string> animatedLeft;

private:
	sf::Texture* texture;
	std::queue<Point*> target;
};

#endif Entity_Zim
