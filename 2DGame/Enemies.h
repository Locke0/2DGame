#include <vector>
#include <ctime>
#include "Game.h"

class Enemies : public Game
{
private:
	//Var
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemyNum;

	//Func
	void initEnemies();

public:
	Enemies();
	~Enemies();
	
	//Func
	void spawnEnemy();

	void updateEnemies();
	void renderEnemies();

};