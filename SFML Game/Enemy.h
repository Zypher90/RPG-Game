#pragma once
#include"Player.h"

class Enemy
{
public:
	sf::Sprite sprite;

	sf::Texture idleTexture;
	sf::Texture walkTexture;
	sf::Texture runTexture;

private:

public:
	void randomMovement();

	void playIdleLoop();
	void playWalkLoop();
	void playRunLoop();

	void Load();
	void Draw(sf::RenderWindow& window);
	void Update();

	bool playerDetected(Player& player);

private:
};

