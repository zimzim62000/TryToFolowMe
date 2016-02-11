#include "game_state.h"
#include "main_menu.h"
#include "config.h"

game_state coreState; 
bool quitGame = false;

int main()
{
	srand(time(NULL));
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	sf::RenderWindow window(sf::VideoMode(Config::screen_width, Config::screen_height), "Follow me", sf::Style::Close, antialiasing);
	//window.setFramerateLimit(30);
	coreState.SetWindow(&window);
	coreState.SetState(new main_menu());

	sf::Clock deltaTime; float dt=0.001;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		coreState.Update(Config::FPS*dt);
		coreState.Render(Config::FPS*dt);

		dt = deltaTime.restart().asSeconds();

		window.display();

		if (quitGame)
		{
			window.close();
		}
	}

	return 0;
}
