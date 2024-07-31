#pragma once

#include<SFML/Graphics.hpp>
#include "Util.h"

class Player
{
public:
	sf::Sprite sprite;

	sf::Vector2f playerPosition = sprite.getPosition();

	const float walkVelocity = 1, runVelocity = 2.5;
	const float baseBulletVelocity = 0.001;
	const sf::Vector2f c_basePlayerSpeed = sf::Vector2f(0.10, 0.10);
	const sf::Vector2i c_playerSpriteResolution = sf::Vector2i(64, 64);


private:
	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture runTexture;


public:
	Player(const sf::Vector2f& origin);
	Player(const sf::Vector2f& origin, const sf::Vector2f& initPos);

	void Load();
	void Shoot(sf::RenderWindow& window);

	void playIdleLoop(int& frameConsolidationCounter);
	void playWalkLoop(int& frameConsolidationCounter);
	void playRunLoop();

	void Update(int& frameConsolidationCounter, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition();
	void setTexture(const sf::Texture& texture);
	void setOrigin(const sf::Vector2f& origin);

private:

};