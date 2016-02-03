#include "main_game.h"
#include "main_menu.h"


void main_game::Initialize(sf::RenderWindow* window)
{
	this->paused = this->mouseClickRight = this->onMouseClickRight = false;

	this->manager = new EntityManager();

	this->map = new MyMap(manager);

	this->map->Load("map4.json");

	this->manager->Add("player", new Player(this->manager, this->map, this->map->tileWidth, 0 , 5.0f));

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");

	this->pausedText = new sf::Text("Paused\nPress Space to Quit\nPress Enter to Resume", *this->font, 96U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->zoom = 0;
	this->currentZoom = 1;
}

void main_game::DebugMode(sf::RenderWindow* window)
{
	this->debugKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2);

	Entity* player = this->manager->Get("player");
	
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{

			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				this->mouseClickRight = true;
			}
		}

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0) {
				this->zoom++;
			}else if (event.mouseWheelScroll.delta < 0) {
				this->zoom--;
			}
			if (this->zoom == 0 ) {
				this->zoom = 0;
				sf::View view = window->getDefaultView();
				this->currentZoom = 1;
				view.zoom(this->currentZoom );
				window->setView(view);
			}
			if (this->zoom > 1) {
				this->zoom = 1;
				sf::View view = window->getDefaultView();
				this->currentZoom = 2;
				view.zoom(this->currentZoom);
				view.setSize(window->getSize().x*2, window->getSize().y * 2);
				window->setView(view);
			}
			if (this->zoom < -1) {
				this->zoom = -1;
				sf::View view = window->getDefaultView();
				this->currentZoom = 0.5f;
				view.zoom(this->currentZoom);
				view.setSize(window->getSize().x / 2, window->getSize().y / 2);
				window->setView(view);
			}
		}
		if (event.type == sf::Event::Closed)
			window->close();
	}
	

	if (this->mouseClickRight == true) {
		
		this->mouseClickRight = false;
		sf::Vector2i position = sf::Mouse::getPosition(*window);
		std::cout << "before " << "x : " << position.x << " y : " << position.y << " zoom : " << this->currentZoom << std::endl;
		std::cout << "player " << "x : " << player->getPosition().x << " y : " << player->getPosition().y << std::endl;
		position.x = position.x * this->currentZoom;
		position.y = position.y * this->currentZoom;
		sf::View view = window->getDefaultView();
		if (player->getPosition().x+player->getTextureRect().width / 2 > view.getSize().x / 2) {
			position.x += player->getPosition().x + player->getTextureRect().width / 2 - view.getSize().x / 2;
		}
		if (player->getPosition().y+player->getTextureRect().height /2 > view.getSize().y / 2) {
			position.y += player->getPosition().y + player->getTextureRect().height / 2 - view.getSize().y / 2;
		}
		std::cout << "after " << "x : " << position.x << " y : " << position.y << " zoom : " << this->currentZoom << std::endl;
		if(position.x > 0 && position.x < this->map->width*this->map->tileWidth && position.y > 0 && position.y < this->map->height*this->map->tileHeight)
		{
			std::pair<int, int> pos = this->map->ConvertPosition(position.x, position.y, this->currentZoom);
			if(this->map->getOnThisPositionNoeud(pos.first, pos.second).passable == 1){
				std::queue<Point*> roadMap = this->map->CalculateParcours(player->getPosition(), position, window, this->currentZoom);
				while (roadMap.size() > 0) {
					player->AddTarget(roadMap.front()->x, roadMap.front()->y);
					roadMap.pop();
				}
				roadMap.empty();
			}
			else {
				std::cout << "Not a passable case" << std::endl;
			}
		}
		else {
			std::cout << "out side the map" << std::endl;
		}
	}
}


void main_game::Update(float const dt, sf::RenderWindow* window)
{
	this->pauseKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);

	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);

	this->DebugMode(window);

	if(this->paused){
		if(this->enterKey){
			this->paused = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
			sf::View view = window->getDefaultView();
			view.reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
			window->setView(view);
			coreState.SetState(new main_menu());
			return;
		}
	}else{
		if (!this->manager->Update(dt, window))
		{
			return;
		}
	}

	if(this->pauseKey && !this->paused){
		this->paused = true;
		sf::View view = window->getDefaultView();
		this->pausedText->setPosition(view.getCenter().x, view.getCenter().y);
		return;
	}

}
void main_game::Render(float const dt, sf::RenderWindow* window)
{
	window->draw(*this->map);
	this->manager->Render(dt, window);

	if(this->paused){
		window->draw(*this->pausedText);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
}