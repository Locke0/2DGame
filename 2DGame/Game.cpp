#include "Game.h"

Game::Game()
{
	this->initVar();
	this->initWindow();
	this->initEnemies();
	this->initMe();
}

Game::~Game()
{
	delete this->window;
}


const bool Game::isRunning() const
{
	return this->window->isOpen();
}

//Func
void Game::initVar()
{
	this->window = nullptr;

	//Game Logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemyNum = 5;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "THE MAZE", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(20.f, 20.f);
	this->enemy.setSize(sf::Vector2f(30.f, 30.f));
	this->enemy.setFillColor(CRed);
	//this->enemy.setOutlineColor(sf::Color::Black);
	//this->enemy.setOutlineThickness(1.f);
}

void Game::initMe()
{
	this->me.setPosition(400.f, 300.f);
	this->me.setRadius(20);
	this->me.setPointCount(3);
	this->me.setFillColor(CBlue);
	this->me.setOutlineColor(sf::Color::Black);
	this->me.setOutlineThickness(1.f);

}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			if (ev.key.code == sf::Keyboard::F)
				this->window->close();
				//this->window->create(this->videoMode, "Maze", sf::Style::Fullscreen);
			break;

		}
	}
}

void Game::update()
{	
	this->pollEvents();

	if (this->endGame == false)
	{
		//Update mouse position
		this->updateMousePositions();

		//Update enemies
		this->updateEnemies();
	}

	//End game condition
	if (this->health <= 0)
		this->endGame = true;

}

void Game::updateMousePositions()
{
	/*
		@return void

		Updates the mouse positions

		- Mouse position relative to window (Vector2i)

	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their colors and positions
		- sets a random position
		- sets a random color
		- adds the enemy to the vector
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>((this->window->getSize().x - this->enemy.getSize().x))),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//Spawn enemies
	this->enemies.push_back(this->enemy);

}

void Game::updateEnemies()
{
	/*
		@return void

		- Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max.
		- Moves the enemies.
		- Removes the enemies at the edge of the screen
	*/

	//Update the timer
	if (this->enemies.size() < this->maxEnemyNum)
	{	
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Optimize this algo: have my own vector class to avoid resizing vectors
	// 
	//Move and update enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 1.f);

		//Delete out of bound enemies
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{	
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain points
					this->points += 1.f;
					
				}
			}

		}
		else
			this->mouseHeld = false;
	}

}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		@return void
		- Clear old frame
		- Render objects
		- Display frame in window
	*/

	this->window->clear(sf::Color::Black);
	
	//Draw game objects
	this->renderEnemies();
	this->window->draw(this->me);


	this->window->display();
}