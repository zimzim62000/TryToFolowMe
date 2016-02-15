#include "entity.h"
#include "point.h"
#include "map.h"
#include "Utility.h"

Entity::Entity(const float speed)
{
	this->texture = new sf::Texture();
	this->active = 1;
	this->groupId = 0;
	this->speed = speed;
	this->IsAnimate = false;
	this->IsONScene = false;
}

Entity::Entity()
{
	this->texture = new sf::Texture();
	this->active = 1;
	this->groupId = 0;
	this->speed = 1;
	this->IsAnimate = false;
	this->IsONScene = false;
}

void Entity::setOnScene(const bool enable)
{
	this->IsONScene = enable;
}

bool Entity::getOnScene()
{
	return this->IsONScene;
}

void Entity::setName(const std::string name)
{
	this->name = name;
}

std::string Entity::getName()
{
	return this->name;
}

void Entity::AnimateMe(const float dt)
{
	if(this->IsAnimate){
		if (this->velocity.x > 0 && this->velocity.y == 0) {
			this->animateRightCount += dt;
			if (this->animateRightCount >= this->animateMax) {
				this->animateRightCount = 0;
				this->animateRightKey++;
				if (this->animateRightKey >= this->animatedRight.size()) {
					this->animateRightKey = 0;
				}
				this->Load(this->animatedRight.at(this->animateRightKey));
			}
		}else if (this->velocity.x < 0 && this->velocity.y == 0) {
			this->animateLeftCount += dt;
			if (this->animateLeftCount >= this->animateMax) {
				this->animateLeftCount = 0;
				this->animateLeftKey++;
				if (this->animateLeftKey >= this->animatedLeft.size()) {
					this->animateLeftKey = 0;
				}
				this->Load(this->animatedLeft.at(this->animateLeftKey));
			}
		}else {
			//if (this->velocity.x == 0 && this->velocity.y == 0) {
				this->animateCount += dt;
				if (this->animateCount >= this->animateMax) {
					this->animateCount = 0;
					this->animateKey++;
					if (this->animateKey >= this->animated.size()) {
						this->animateKey = 0;
					}
					this->Load(this->animated.at(this->animateKey));
				}
			//}
		}
	}
}

void Entity::SetNewAnimation(std::string nameAnimation)
{
	this->animated.push_back(nameAnimation);
}

void Entity::SetNewRightAnimation(std::string nameAnimation)
{
	this->animatedRight.push_back(nameAnimation);
}

void Entity::SetNewLeftAnimation(std::string nameAnimation)
{
	this->animatedLeft.push_back(nameAnimation);
}

bool Entity::getBusy()
{
	return this->busy;
}

void Entity::Load(std::string filename)
{
	this->texture->loadFromFile("Graphics/Images/" + filename);
	this->setTexture(*this->texture);
}

bool Entity::Update(float const dt, sf::RenderWindow* window)
{
	this->move(this->velocity * this->speed * dt);
	this->AnimateMe(dt);
	return true;
}
void Entity::Collision(Entity* entity)
{
}

bool Entity::CheckCollision(Entity* entity)
{
	return this->getGlobalBounds().intersects(entity->getGlobalBounds());
}

int Entity::GroupID()
{
	return this->groupId;
}

int Entity::Active()
{
	return this->active;
}

void Entity::Destroy()
{
	this->active = 0;
}

Entity::~Entity()
{
	delete this->texture;
	target.empty();
}



void Entity::MoveOnTarget(float const dt)
{
	if (this->target.size() > 0) {
		Point* targetOne = this->target.front();
		if (this->velocity.x == 0 && this->velocity.y == 0) {
			sf::Vector2f diff = Utility::diffVecteur2(sf::Vector2f(targetOne->x, targetOne->y), sf::Vector2f(this->getPosition().x, this->getPosition().y));
			this->velocity = Utility::normalizeVecteur(diff);
		}
		if (abs(abs(targetOne->x) - abs(this->getPosition().x)) <= abs(this->speed*this->velocity.x*dt) && abs(abs(targetOne->y)- abs(this->getPosition().y)) <= abs(this->speed*this->velocity.y*dt)) {
			this->setPosition(targetOne->x, targetOne->y);
			this->velocity.x = 0;
			this->velocity.y = 0;
			this->target.pop();
		}
	}else{
		this->onMove = false;
		this->busy = false;
	}
}

void Entity::AddTarget(const int x, const int y)
{
	this->busy = true;
	this->onMove = true;
	Point* pt = new Point(x, y);
	this->target.push(pt);
}

bool Entity::getOnMovement() {
	return this->onMove;
}