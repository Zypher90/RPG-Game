#pragma once

#include<SFML/Graphics.hpp>


class Util{
public:

	static void initTextBoxes();
	static void showFPS(sf::Clock& clock, int& fpsCounterInt, sf::RenderWindow& window);

	static sf::Vector2f normalize(sf::Vector2f& vector);
	static sf::Vector2i normalize_int(sf::Vector2i& vector);

};
