#include "Util.h"

using namespace std;

sf::Text fpsCounterText;
sf::Font helveticaFont;

int Util::singleLeftClickFlag = 0;

//============================================ INITIALIZATION AND GENERAL ==========================================================
void Util::initTextBoxes() {
    if (!helveticaFont.loadFromFile("Assets/Fonts/Helvetica/Helvetica.ttf"))
        cout << "Couldn't load Helvetica font" << endl;
    fpsCounterText.setFont(helveticaFont);
    fpsCounterText.setCharacterSize(20);
    fpsCounterText.setFillColor(sf::Color::White);
    fpsCounterText.setStyle(sf::Text::Bold);
    fpsCounterText.setPosition(sf::Vector2f(700, 0));
}

void Util::unitize(sf::Vector2f& vector) {
    float m = vector.x * vector.x + vector.y * vector.y;
    vector.x = vector.x / m;
    vector.y = vector.y / m;
}

void Util::unitize_int(sf::Vector2i& vector) {
    float m = vector.x * vector.x + vector.y * vector.y;
    vector.x = vector.x / m;
    vector.y = vector.y / m;
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
//=============================================================================================================================


//============================================= EVENT DETECTION ===============================================================
bool Util::runTriggerActivated() {
    /*sf::Event runTrigger;
    while (window.pollEvent(runTrigger)) {
        if (runTrigger.type == sf::Event::KeyPressed) {
            if (runTrigger.key.code == sf::Keyboard::LShift) {
                cout << "shift pressed" << endl;
                return true;
            }
        }
    }*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        return true;
    }
    return false;
}

bool Util::walkTriggerActivated() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        return true;
    }
    return false;
}

bool Util::anyKeyPressed() {
    for (int i = -1; i < sf::Keyboard::KeyCount; ++i) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            return false;
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
            return true;
    }
    return false;
}

bool Util::isMouseLeftButtonClicked() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    singleLeftClickFlag = 0;
    return false;
}

bool Util::playerBulletDeletionValidated(sf::RectangleShape& bullet) {
    float x = bullet.getPosition().x;
    float y = bullet.getPosition().y;
    if (x > 800 || x < 0 || y>800 || y < 0) {
        return true;
    }
    return false;
}
//=============================================================================================================================