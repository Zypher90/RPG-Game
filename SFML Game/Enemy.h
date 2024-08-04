#pragma once
#include"Player.h"

class Enemy
{
public:
	const sf::Vector2f c_baseEnemyVel = sf::Vector2f(0.10, 0.10);
	const sf::Vector2i enemyResolution = sf::Vector2i(64, 64);

	sf::Sprite sprite;

	sf::Vector2f finalPos = sf::Vector2f(0, 0);

private:
	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture runTexture;

	int idleHorizontalIndex = 0;
	int walkHorizontalIndex = 0;
	int runHorizontalIndex = 0;

public:
	Enemy(const sf::Vector2f& origin, const sf::Vector2f& initPos);

	void randomMovement(int& frameConsolidationCounter);

	void walkForward();
	void walkBackward();
	void walkLeft();
	void walkRight();

	void runForward();
	void runBackward();
	void runRight();
	void runLeft();

	void playIdleLoop(int& frameConsolidationCounter);

	void Load();
	void Draw(sf::RenderWindow& window);
	void Update(int& frameConsolidationCounter, Player& player);

	bool playerDetected(Player& player);

	int moveDirection();
	int moveDistance();
private:
};

