#pragma once

#include<SFML/Graphics.hpp>

class Player
{

	/*Player(sf::Vector2f& initialPosition) {
		this->setPosition(initialPosition);
	}

	Player(sf::Vector2f& initialPosition, sf::Texture& initialTexture) {
		this->setPosition(initialPosition);
		this->setTexture(initialTexture);
	}*/

public:
	sf::Sprite sprite;

	sf::Vector2f playerPosition = sprite.getPosition();

	const sf::Vector2f c_basePlayerSpeed = sf::Vector2f(0.10, 0.10);
	const sf::Vector2i c_playerSpriteResolution = sf::Vector2i(64, 64);

private:
	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture runTexture;


public:
	void Load();
	//void Load(sf::Texture texture);

	void playIdleLoop();
	void playWalkLoop();
	void playRunLoop();

	void Update();
	void Draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f& position);
	sf::Vector2f getPosition();
	void setTexture(const sf::Texture& texture);

private:

};