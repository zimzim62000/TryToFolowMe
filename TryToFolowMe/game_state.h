#ifndef GameState_Zim
#define GameState_Zim


#pragma once

#include <SFML/Graphics.hpp>


class tiny_state
{
public:
	virtual void Initialize(sf::RenderWindow* window)
	{
	}

	virtual void Update(float const dt, sf::RenderWindow* window)
	{
	}

	virtual void Render(float const dt, sf::RenderWindow* window)
	{
	}

	virtual void Destroy(sf::RenderWindow* window)
	{
	}
};

class game_state
{
public:
	game_state()
	{
		this->state = NULL;
	}

	void SetWindow(sf::RenderWindow* window)
	{
		this->window = window;
	}

	void SetState(tiny_state* state)
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Initialize(this->window);
		}
	}

	void Update(float const dt)
	{
		if (this->state != NULL)
		{
			this->state->Update(dt, this->window);
		}
	}
	void Render(float const dt)
	{
		if (this->state != NULL)
		{
			this->state->Render(dt, this->window);
		}
	}

	~game_state()
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
	}
private:
	sf::RenderWindow* window;
	tiny_state* state;
	float deltaT;
};

extern game_state coreState;
extern bool quitGame;

#endif GameState_Zim
