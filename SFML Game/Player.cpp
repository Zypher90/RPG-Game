#include "Player.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>

using namespace std;

int idleHorizontalIndex = 0, idleVerticalIndex = 0;
int walkHorizontalIndex = 0, walkVerticalIndex = 0;
int singleLeftMouseClickFlag = 0;

vector<sf::RectangleShape> bulletVec;
vector<sf::Vector2f> bulletDir;

sf::Vector2f heading;

static bool anyKeyPressed();
static bool walkTriggerActivated();
static bool isMouseLeftButtonClicked();
static bool playerBulletDeletionValidated(sf::RectangleShape& bullet);

//===================================================== CONSTRUCTORS ===================================================================

Player::Player(const sf::Vector2f& origin) {
    setOrigin(origin);
}

Player::Player(const sf::Vector2f& origin, const sf::Vector2f& initPos) {
    setOrigin(origin);
    setPosition(initPos);
}

//======================================================================================================================================


//----------------------------------------------------------- EVENT FUNCTIONS --------------------------------------------------------
void Player::Shoot(sf::RenderWindow& window) {
    if (isMouseLeftButtonClicked() && singleLeftMouseClickFlag == 0) {
        singleLeftMouseClickFlag = 1;
        bulletVec.push_back(sf::RectangleShape(sf::Vector2f(20, 5)));
        int i = bulletVec.size() - 1;
        bulletVec[i].setPosition(this->getPosition());
        heading = sf::Vector2f(sf::Mouse::getPosition(window)) - this->getPosition();
        bulletVec[i].setRotation(atan(heading.y / heading.x) * 180 / 3.14);
        heading.x = heading.x * baseBulletVelocity;
        heading.y = heading.y * baseBulletVelocity;
        bulletDir.push_back(heading);
        return;
    }
}

void Player::Load() {
    if (!idleTexture.loadFromFile("Assets/Spritesheets/Player-Male/Unarmed_Idle/Unarmed_Idle_full.png"))
    {
        cout << "Ran into error loading player idle loop spritesheet" << endl;
    }

    if(!walkTexture.loadFromFile("Assets/Spritesheets/Player-Male/Unarmed_Walk/Unarmed_Walk_full.png"))
    {
        cout << "Ran into error loading player walk loop spritesheet" << endl;
    }

    if (!runTexture.loadFromFile("Assets/Spritesheets/Player-Male/Unarmed_Run/Unarmed_Run_full.png"))
    {
        cout << "Ran into error loading player run loop spritesheet" << endl;
    }
}

void Player::Update(int& frameConsolidationCounter, sf::RenderWindow& window) {
    this->Shoot(window);
    for (int i = 0; i < bulletVec.size(); i++) {
        bulletVec[i].setPosition(bulletVec[i].getPosition() + bulletDir[i]);       
        if (playerBulletDeletionValidated(bulletVec[i])) {
            bulletVec.erase(bulletVec.begin() + i);
            bulletDir.erase(bulletDir.begin() + i);
        }
    }
    if (!anyKeyPressed()) {
        this->playIdleLoop(frameConsolidationCounter);
        return;
    }
    if (walkTriggerActivated()) {
        this->playWalkLoop(frameConsolidationCounter);
        return;
    }
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
    for (auto i : bulletVec) {
        window.draw(i);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------









//-------------------------------------------------- ANIMATION FUNCTIONS --------------------------------------------------------------
void Player::playIdleLoop(int& frameConsolidationCounter) {

    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(idleHorizontalIndex * 64, idleVerticalIndex * 64), c_playerSpriteResolution));
    sprite.setScale(3, 3);

    if (idleHorizontalIndex == 5) {
        idleHorizontalIndex = 0;
    }

    if (frameConsolidationCounter % 500 == 0) {
        idleHorizontalIndex++;
    }
     
     walkHorizontalIndex = 0;
}

void Player::playWalkLoop(int& frameConsolidationCounter) {
    sprite.setTexture(walkTexture);
    sprite.setScale(3, 3);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        walkVerticalIndex = 3;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(sprite.getPosition() + sf::Vector2f(c_basePlayerSpeed.x * 0, c_basePlayerSpeed.y * -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        walkVerticalIndex = 0;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(sprite.getPosition() + sf::Vector2f(c_basePlayerSpeed.x * 0, c_basePlayerSpeed.y * 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        walkVerticalIndex = 1;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(sprite.getPosition() + sf::Vector2f(c_basePlayerSpeed.x * -1, c_basePlayerSpeed.y * 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        walkVerticalIndex = 2;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(sprite.getPosition() + sf::Vector2f(c_basePlayerSpeed.x * 1, c_basePlayerSpeed.y * 0));
    }

    if (walkHorizontalIndex == 5) {
        walkHorizontalIndex = 0;
    }
    
    if (frameConsolidationCounter % 200 == 0) {
        walkHorizontalIndex++;
    }

    idleHorizontalIndex = 0;
    idleVerticalIndex = 0;
}

//------------------------------------------------------------------------------------------------------------------------------------







//--------------------------------------------------- GETTERS AND SETTERS ----------------------------------------------------------
sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}

void Player::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Player::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Player::setOrigin(const sf::Vector2f& origin) {
    sprite.setOrigin(origin);
}

//------------------------------------------------------------------------------------------------------------------------------------






//--------------------------------------------------- STATIC LOGIC FUNCTIONS ---------------------------------------------------------
static bool runTriggerActivated() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        return true;
    }
    return false;
}

static bool walkTriggerActivated() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        return true;
    }
    return false;
}

static bool anyKeyPressed() {
    for (int i = -1; i < sf::Keyboard::KeyCount; ++i) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
            return true;
    }
    return false;
}

static bool isMouseLeftButtonClicked() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    singleLeftMouseClickFlag = 0;
    return false;
}

static bool playerBulletDeletionValidated(sf::RectangleShape& bullet) {
    float x = bullet.getPosition().x;
    float y = bullet.getPosition().y;
    if (x > 800 || x < 0 || y>800 || y < 0) {
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------