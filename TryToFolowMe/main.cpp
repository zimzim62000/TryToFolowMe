#include "game_state.h"
#include "main_menu.h"

game_state coreState; 
bool quitGame = false;


const int FPS = 60;
const int screen_width = 1280;
const int screen_height = 768;

int main()
{
	srand(time(NULL));
	sf::ContextSettings antialiasing;
	antialiasing.antialiasingLevel = 32;
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Follow me", sf::Style::Default, antialiasing);
	//window.setFramerateLimit(60);
	coreState.SetWindow(&window);
	coreState.SetState(new main_menu());

	sf::Clock deltaTime; float dt=0.001;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		/*
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{

				}
			}
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		*/
		window.clear(sf::Color::Black);

		coreState.Update(dt*FPS);
		coreState.Render(dt*FPS);

		dt = deltaTime.restart().asSeconds();

		window.display();

		if (quitGame)
		{
			window.close();
		}
	}

	return 0;
}