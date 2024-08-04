#pragma once

#include "Util.h"

class Player
{
public:
	sf::Sprite sprite;

	sf::Vector2f playerPosition = sprite.getPosition();

	const float walkVelocity = 1, runVelocity = 2.5;
	const float baseBulletVelocity = 500;
	const sf::Vector2f c_basePlayerSpeed = sf::Vector2f(0.10, 0.10);
	const sf::Vector2i c_playerSpriteResolution = sf::Vector2i(64, 64);

private:
	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture runTexture;


	int idleHorizontalIndex = 0, idleVerticalIndex = 0;
	int walkHorizontalIndex = 0, walkVerticalIndex = 0;
	int runHorizontalIndex = 0, runVerticalIndex = 0;

public:
	Player(const sf::Vector2f& origin, const sf::Vector2f& initPos);

	void Load();
	void Shoot(sf::RenderWindow& window);

	void playIdleLoop(int& frameConsolidationCounter);
	void playWalkLoop(int& frameConsolidationCounter);
	void playRunLoop(int& frameConsolidationCounter);

	void Update(int& frameConsolidationCounter, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	void setTexture(const sf::Texture& texture);
	void setOrigin(const sf::Vector2f& origin);

private:

};