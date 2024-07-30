#include "Player.h"
#include<iostream>

using namespace std;

int idleHorizontalIndex = 0, idleVerticalIndex = 0;
int walkHorizontalIndex = 0, walkVerticalIndex = 0;

int frameConsolidation = 0;

static bool anyKeyPressed();
static bool walkTriggerActivated();

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

void Player::Update() {
    if (!anyKeyPressed()) {
        playIdleLoop();
        return;
    }
    if (walkTriggerActivated()) {
        playWalkLoop();
        return;
    }
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Player::playIdleLoop() {

    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(idleHorizontalIndex * 64, idleVerticalIndex * 64), c_playerSpriteResolution));
    sprite.setScale(3, 3);

    if (idleVerticalIndex == 3 && idleHorizontalIndex == 3) {
        idleVerticalIndex = 0;
        idleHorizontalIndex = 0;
    }

    if (idleHorizontalIndex == 11) {
        idleHorizontalIndex = 0;
        idleVerticalIndex++;
    }

     idleHorizontalIndex++;
     
     walkHorizontalIndex = 0;
}

void Player::playWalkLoop() {
    sprite.setTexture(walkTexture);
    sprite.setScale(3, 3);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        walkVerticalIndex = 3;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(playerPosition + sf::Vector2f(c_basePlayerSpeed.x * 0, c_basePlayerSpeed.y * -1));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        walkVerticalIndex = 0;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(playerPosition + sf::Vector2f(c_basePlayerSpeed.x * 0, c_basePlayerSpeed.y * 1));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        walkVerticalIndex = 1;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(playerPosition + sf::Vector2f(c_basePlayerSpeed.x * -1, c_basePlayerSpeed.y * 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        walkVerticalIndex = 2;
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(walkHorizontalIndex * 64, walkVerticalIndex * 64), c_playerSpriteResolution));
        sprite.setPosition(playerPosition + sf::Vector2f(c_basePlayerSpeed.x * 1, c_basePlayerSpeed.y * 0));
    }

    if (walkHorizontalIndex == 5) {
        walkHorizontalIndex = 0;
    }
    walkHorizontalIndex++;

    idleHorizontalIndex = 0;
    idleVerticalIndex = 0;
}

sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}

void Player::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Player::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}


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