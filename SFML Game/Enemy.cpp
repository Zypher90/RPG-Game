#include "Enemy.h"

using namespace std;

bool inRandomMovement = false;

int movedir = 0;
int movedis = 0;

sf::Clock enemyMovementClock;

//----------------------------------------------------------- CONSTRUCTORS --------------------------------------------------------

Enemy::Enemy(const sf::Vector2f& origin, const sf::Vector2f& initPos) {
	this->sprite.setOrigin(origin);
	this->sprite.setPosition(initPos);
}

//------------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------- EVENT FUNCTIONS --------------------------------------------------------
void Enemy::Load() {
	if (!this->idleTexture.loadFromFile("Assets/Spritesheets/Player-Female/Unarmed_Idle/Unarmed_Idle_full.png"))
		cout << "problem loading enemy idle texture" << endl;
	if (!this->walkTexture.loadFromFile("Assets/Spritesheets/Player-Female/Unarmed_Walk/Unarmed_Walk_full.png"))
		cout << "problem loading enemy walk texture" << endl;
	if (!this->runTexture.loadFromFile("Assets/Spritesheets/Player-Female/Unarmed_Run/Unarmed_Run_full.png"))
		cout << "problem loading enemy run texture" << endl;
}

void Enemy::Update(int& frameConsolidationCounter, Player& player) {
	if (playerDetected(player)) {
		return;
	}
	this->randomMovement(frameConsolidationCounter);
	if (!inRandomMovement) {
		this->playIdleLoop(frameConsolidationCounter);
		return;
	}
}

void Enemy::Draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}
//------------------------------------------------------------------------------------------------------------------------------------


//============================================================ ANIMATIONS ============================================================

void Enemy::randomMovement(int& frameConsolidationCounter) {
	float t = enemyMovementClock.getElapsedTime().asSeconds();
	if (t > 9.8 && t < 10.2) {
		enemyMovementClock.restart();
		movedir = this->moveDirection();
		movedis = this->moveDistance();
		inRandomMovement = true;
		switch (movedir)
		{
		case 1:
			this->finalPos.x = this->sprite.getPosition().x;
			this->finalPos.y = this->sprite.getPosition().y - movedis;
			break;
		case 2:
			this->finalPos.x = this->sprite.getPosition().x;
			this->finalPos.y = this->sprite.getPosition().y + movedis;
			break;
		case 3:
			this->finalPos.x = this->sprite.getPosition().x - movedis;
			this->finalPos.y = this->sprite.getPosition().y;
			break;
		case 4:
			this->finalPos.x = this->sprite.getPosition().x + movedis;
			this->finalPos.y = this->sprite.getPosition().y;
			break;
		default:
			cout << "invalid direction argument" << endl;
			break;
		}
	}

	if (floor(this->sprite.getPosition().x) == floor(this->finalPos.x) && floor(this->sprite.getPosition().y) == floor(this->finalPos.y)) {
		inRandomMovement = false;
		walkHorizontalIndex = 0;
	}

	if (inRandomMovement) {
		switch (movedir)
		{
		case 1:
			this->walkForward();
			break;
		case 2:
			this->walkBackward();
			break;
		case 3:
			this->walkLeft();
			break;
		case 4:
			this->walkRight();
			break;
		default:
			cout << "invalid direction argument " << movedir << endl;
			break;
		}

		if (frameConsolidationCounter % 200 == 0) {
			walkHorizontalIndex++;
		}

		if (walkHorizontalIndex == 5) {
			walkHorizontalIndex = 0;
		}
	}
}

void Enemy::playIdleLoop(int& frameConsolidationCounter) {
	this->sprite.setTexture(this->idleTexture);
	this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(idleHorizontalIndex * 64, 0 * 64), enemyResolution));
	this->sprite.setScale(3, 3);

	if (idleHorizontalIndex == 5) {
		idleHorizontalIndex = 0;
	}

	if (frameConsolidationCounter % 200 == 0) {
		idleHorizontalIndex++;
	}

	walkHorizontalIndex = 0;
	runHorizontalIndex = 0;
}

//=====================================================================================================================================

bool Enemy::playerDetected(Player& player) {
	float m = abs(player.sprite.getPosition().x - this->sprite.getPosition().x);
	float n = abs(player.sprite.getPosition().y - this->sprite.getPosition().y);
	float r = sqrt(m * m + n * n);
	if (r < 100.0f) {
		return true;
	}
	return false;
}

int Enemy::moveDirection() {
	return 1 + Util::randomNumber() % 4;
}

int Enemy::moveDistance() {
	return 15 + Util::randomNumber() % 50;
}

//========================================================== MOVEMENT =============================================================

void Enemy::walkForward() {
	this->sprite.setTexture(this->walkTexture);
	this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(this->walkHorizontalIndex * 64, 3 * 64), enemyResolution));
	this->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(0, -0.10));
}
void Enemy::walkBackward() {
	this->sprite.setTexture(walkTexture);
	this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(this->walkHorizontalIndex * 64, 0 * 64), enemyResolution));
	this->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(0, 0.10));
}
void Enemy::walkLeft() {
	this->sprite.setTexture(walkTexture);
	this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(this->walkHorizontalIndex * 64, 1 * 64), enemyResolution));
	this->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-0.10, 0));
}
void Enemy::walkRight() {
	this->sprite.setTexture(walkTexture);
	this->sprite.setTextureRect(sf::IntRect(sf::Vector2i(this->walkHorizontalIndex * 64, 2 * 64), enemyResolution));
	this->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(0.10, 0));
}


//=================================================================================================================================