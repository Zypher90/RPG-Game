#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<cstdlib>

class Util{
public:
	static int singleLeftClickFlag;

private:

public:

	static void initTextBoxes();
	static void showFPS(sf::Clock& clock, int& fpsCounterInt, sf::RenderWindow& window);

	static void unitize(sf::Vector2f& vector);
	static void unitize_int(sf::Vector2i& vector);

	static bool anyKeyPressed();
	static bool walkTriggerActivated();
	static bool runTriggerActivated();
	static bool isMouseLeftButtonClicked();
	static bool playerBulletDeletionValidated(sf::RectangleShape& bullet);

	static int randomNumber();
};
