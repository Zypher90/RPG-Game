#include "Util.h"
#include<iostream>

using namespace std;

sf::Text fpsCounterText;
sf::Font helveticaFont;


void Util::initTextBoxes() {
   if (!helveticaFont.loadFromFile("Assets/Fonts/Helvetica/Helvetica.ttf"))
       cout << "Couldn't load Helvetica font" << endl;
   fpsCounterText.setFont(helveticaFont);
   fpsCounterText.setCharacterSize(20);
   fpsCounterText.setFillColor(sf::Color::White);
   fpsCounterText.setStyle(sf::Text::Bold);
   fpsCounterText.setPosition(sf::Vector2f(700, 0));
}

sf::Vector2f Util::normalize(sf::Vector2f& vector) {
    int m = vector.x * vector.x + vector.y * vector.y;
    sf::Vector2f unitVector;
    unitVector.x = vector.x / m;
    unitVector.y = vector.y / m;

    return unitVector;
}

sf::Vector2i Util::normalize_int(sf::Vector2i& vector) {
    int m = vector.x * vector.x + vector.y * vector.y;
    sf::Vector2i unitVector;
    unitVector.x = vector.x / m;
    unitVector.y = vector.y / m;

    return unitVector;
}

void Util::showFPS(sf::Clock& clock, int& fpsCounterInt, sf::RenderWindow& window) {

    float x = clock.getElapsedTime().asSeconds();

    if (x > 0.23 && x < 0.27) {
        clock.restart();
        fpsCounterText.setString("FPS:" + to_string(fpsCounterInt * 4));
        fpsCounterInt = 0;
    }
    window.draw(fpsCounterText);
}
