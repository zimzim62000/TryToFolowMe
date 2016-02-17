#include "main_game.h"
#include "main_menu.h"
#include "field.h"
#include "enemy.h"


void main_game::Initialize(sf::RenderWindow* window)
{
	this->paused = this->mouseClickRight = this->onMouseClickRight = this->mouseClickLeft = this->onMouseClickLeft = this->entityActive = false;

	this->manager = new EntityManager();

	this->map = new MyMap(manager);

	this->map->Load("newmap1.json");

	std::pair<int, int> playerPosition = this->map->getPositionavailable();

	Player* player = new Player(this->manager, this->map, playerPosition.first, playerPosition.second, 15.0f);

	this->manager->Add("player", player);

	playerPosition = this->map->getPositionavailable();

	Field* field = new Field(this->manager, this->map, playerPosition.first, playerPosition.second);

	this->manager->Add("field", field);

	/*
	sf::Clock deltaTime;

	for (int(i) = 0; i < 100; i++) {
		playerPosition = this->map->getPositionavailable();

		Enemy* enemy = new Enemy(this->manager, this->map, playerPosition.first, playerPosition.second, 10.0f);

		playerPosition = this->map->getPositionavailable();

		std::queue<Point*> roadMap = this->map->CalculateParcours(enemy->getPosition(), sf::Vector2i(playerPosition.first, playerPosition.second), window, 1);
		while (roadMap.size() > 0) {
			enemy->AddTarget(roadMap.front()->x, roadMap.front()->y);
			roadMap.pop();
		}
		roadMap.empty();

		this->manager->Add("Enemy-" +  std::to_string(i), enemy);
	}

	std::cout << "Generate : " << deltaTime.restart().asSeconds() << std::endl;
	*/

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");

	this->pausedText = new sf::Text("Paused\nPress Space to Quit\nPress Enter to Resume", *this->font, 96U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->zoom = 0;
	this->currentZoom = 4;
	this->camera = new Camera();
	this->camera->reset(sf::FloatRect(0, 0, window->getSize().x*this->currentZoom, window->getSize().y*this->currentZoom));
	this->camera->folowEntity(player);


	this->ActiveEntity = new Entity();

	this->ItemView = sf::View();
}

void main_game::CatchUserAction(sf::RenderWindow* window)
{
	this->debugKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2);
	
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				this->mouseClickRight = true;
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				this->mouseClickLeft = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				this->onMouseClickRight = true;
				this->mouseClickRight = false;
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				this->onMouseClickLeft = true;
				this->mouseClickLeft = false;
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
				this->currentZoom = 4;//1;
				this->camera->zoom(this->currentZoom );
				this->camera->setSize(window->getSize().x * this->currentZoom, window->getSize().y * this->currentZoom);
			}
			if (this->zoom > 1) {
				this->zoom = 1;
				this->currentZoom = 8;// 2;
				this->camera->zoom(this->currentZoom);
				this->camera->setSize(window->getSize().x * this->currentZoom, window->getSize().y * this->currentZoom);
			}
			if (this->zoom < -1) {
				this->zoom = -1;
				this->currentZoom = 2;//0.5f;
				this->camera->zoom(this->currentZoom);
				this->camera->setSize(window->getSize().x * this->currentZoom, window->getSize().y * this->currentZoom);
			}
		}
		if (event.type == sf::Event::Closed)
			window->close();
	}
	
	if (this->mouseClickLeft == true && this->onMouseClickLeft == true) {
		this->onMouseClickLeft = false;


		sf::Vector2i position = this->GetMousePosition(window);
		if (position.x > 0 && position.x < this->map->width*this->map->tileWidth && position.y > 0 && position.y < this->map->height*this->map->tileHeight)
		{
			Entity* entityPosition = this->manager->GetAtThisPosition(position.x, position.y, this->map->tileWidth, this->map->tileHeight);
			if (entityPosition->getOnScene()) {
				this->ActiveEntity = entityPosition;
				this->nameActiveEntity = new sf::Text(this->ActiveEntity->getName(), *this->font, 192U);
			}
		}
	}

	if (this->mouseClickRight == true && this->onMouseClickRight == true && this->ActiveEntity->getOnScene()) {

		if(this->ActiveEntity->getBusy() == false){
			this->onMouseClickRight = false;
			sf::Vector2i position = this->GetMousePosition(window);
			if(position.x > 0 && position.x < this->map->width*this->map->tileWidth && position.y > 0 && position.y < this->map->height*this->map->tileHeight)
			{
				std::pair<int, int> pos = this->map->ConvertPosition(position.x, position.y, this->currentZoom);
				if(this->map->getOnThisPositionNoeud(pos.first, pos.second).passable == 1){
					std::queue<Point*> roadMap = this->map->CalculateParcours(this->ActiveEntity->getPosition(), position, window, this->currentZoom);
					while (roadMap.size() > 0) {
						this->ActiveEntity->AddTarget(roadMap.front()->x, roadMap.front()->y);
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
			std::cout << "Active Entity busy" << std::endl;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->ActiveEntity = new Entity();
		this->camera->move(-10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->ActiveEntity = new Entity();
		this->camera->move(10, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->ActiveEntity = new Entity();
		this->camera->move(0, -10);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->ActiveEntity = new Entity();
		this->camera->move(0, 10);
	}
}

sf::Vector2i main_game::GetMousePosition(sf::RenderWindow* window)
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	position.x = position.x * this->currentZoom;
	position.y = position.y * this->currentZoom;
	//std::cout << "camera" << this->camera->getPosition().x << " - " << player->getPosition().x << std::endl;
	if (this->camera->getPosition().x > this->camera->getSize().x / 2) {
		position.x += this->camera->getPosition().x - this->camera->getSize().x / 2;
	}
	if (this->camera->getPosition().y> this->camera->getSize().y / 2) {
		position.y += this->camera->getPosition().y - this->camera->getSize().y / 2;
	}
	return position;
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
	window->setView(*this->camera);

	window->draw(*this->map);
	this->manager->Render(dt, window);

	if(this->paused){
		window->draw(*this->pausedText);
	}

	if (this->ActiveEntity->getOnScene()) {
		this->ItemView.setViewport(sf::FloatRect(0, 0, 0.1f, 0.1f));
		this->camera->folowEntity(this->ActiveEntity);

		this->nameActiveEntity->setPosition(
			(this->ItemView.getSize().x-this->nameActiveEntity->getGlobalBounds().width)/2,
			(this->ItemView.getSize().y - this->nameActiveEntity->getGlobalBounds().height)/2 );
		window->setView(this->ItemView);
		window->draw(*this->nameActiveEntity);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
	delete this->camera;
	delete this->map;
	delete this->manager;
	delete this->ActiveEntity;
	delete this->font;
	delete this->pausedText;
}