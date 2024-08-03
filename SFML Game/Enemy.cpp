#include "Enemy.h"

using namespace std;



//----------------------------------------------------------- EVENT FUNCTIONS --------------------------------------------------------
void Enemy::Load() {
	if (!this->idleTexture.loadFromFile("Assets/Spritesheets/Player-Female/Unarmed_Idle/Unarmed_Idle_full.png"))
		cout << "problem loading enemy idle texture" << endl;
	if (!this->walkTexture.loadFromFile("Assets/Spritesheets/Player-Female/Umarmed_Walk/Unarmed_Walk_full.png"))
		cout << "problem loading enemy walk texture" << endl;
	if (!this->runTexture.loadFromFile("Assets/Spritesheets/Player-Female/Unarmed_Run/Unarmed_Run_full.png"))
		cout << "problem loading enemy run texture" << endl;
}

void Enemy::Update() {
	if (!playerDetected) {
		this->randomMovement();
	}
}

void Enemy::Draw(sf::RenderWindow& window) {
	window.draw(this->sprite);
}
//------------------------------------------------------------------------------------------------------------------------------------

void Enemy::randomMovement() {
	if (Util::randomNumber() == 1) {

	}
}
bool Enemy::playerDetected(Player& player) {

}