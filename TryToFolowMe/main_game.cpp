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
	this->camera = new Camera();
	this->camera->reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
}

void main_game::CatchUserAction(sf::RenderWindow* window)
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
				this->mouseClickRight = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				this->onMouseClickRight = true;
				this->mouseClickRight = false;
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
				this->currentZoom = 1;
				this->camera->zoom(this->currentZoom );
			}
			if (this->zoom > 1) {
				this->zoom = 1;
				this->currentZoom = 2;
				this->camera->zoom(this->currentZoom);
				this->camera->setSize(window->getSize().x*2, window->getSize().y * 2);
			}
			if (this->zoom < -1) {
				this->zoom = -1;
				this->currentZoom = 0.5f;
				this->camera->zoom(this->currentZoom);
				this->camera->setSize(window->getSize().x / 2, window->getSize().y / 2);
			}
		}
		if (event.type == sf::Event::Closed)
			window->close();
	}
	

	if (this->mouseClickRight == true && this->onMouseClickRight == true) {

		if(player->getBusy() == false){
			this->onMouseClickRight = false;
			sf::Vector2i position = sf::Mouse::getPosition(*window);
			position.x = position.x * this->currentZoom;
			position.y = position.y * this->currentZoom;

			if (player->getPosition().x+player->getTextureRect().width / 2 > this->camera->getSize().x / 2) {
				position.x += player->getPosition().x + player->getTextureRect().width / 2 - this->camera->getSize().x / 2;
			}
			if (player->getPosition().y+player->getTextureRect().height /2 > this->camera->getSize().y / 2) {
				position.y += player->getPosition().y + player->getTextureRect().height / 2 - this->camera->getSize().y / 2;
			}
			if(position.x > 0 && position.x < this->map->width*this->map->tileWidth && position.y > 0 && position.y < this->map->height*this->map->tileHeight)
			{
				std::pair<int, int> pos = this->map->ConvertPosition(position.x, position.y, this->currentZoom);
				//std::cout << "pos x : " << position.x << " pos y : " << position.y << " convert x : " << pos.first << " y " << pos.second << std::endl;
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
				std::cout << "outside the map" << std::endl;
			}
		}else {
			std::cout << "Player busy" << std::endl;
		}
	}
}


void main_game::Update(float const dt, sf::RenderWindow* window)
{
	this->pauseKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);

	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);

	this->CatchUserAction(window);

	if(this->paused){
		if(this->enterKey){
			this->paused = false;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
			this->camera->reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
			window->setView(*this->camera);
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
		this->pausedText->setPosition(this->camera->getCenter().x, this->camera->getCenter().y-this->pausedText->getGlobalBounds().height/2);
		return;
	}

}
void main_game::Render(float const dt, sf::RenderWindow* window)
{
	Entity* player = this->manager->Get("player");
	this->camera->folowEntity(player);
	window->setView(*this->camera);

	window->draw(*this->map);
	this->manager->Render(dt, window);

	if(this->paused){
		window->draw(*this->pausedText);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
}