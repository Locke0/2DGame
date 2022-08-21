#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Game Engine
*/

class Game
{
private:
	//Var
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	std::vector<std::string> map_sketch;

	sf::Color CGreen = sf::Color(242, 181, 55, 255);
	sf::Color CWhite = sf::Color(245, 246, 246, 255);
	sf::Color CBlue = sf::Color(152, 173, 192, 255);
	sf::Color CRed = sf::Color(150, 95, 76, 255);
	sf::Color CPurple = sf::Color(55, 52, 79, 255);

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemyNum;

	bool mouseHeld;
	
	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::CircleShape me;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Func
	void initVar();
	void initWindow();
	void initEnemies();
	void initMe();

public:
	Game();
	virtual ~Game();

	//Accessors
	const bool isRunning() const;
	const bool getEndGame() const;

	//Functions
	

	void pollEvents();
	
	void update();
	void updateMousePositions();
	
	void spawnEnemy();
	void updateEnemies();
	
	void renderEnemies();

	void render();
	

};