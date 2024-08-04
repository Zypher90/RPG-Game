#include "Player.h"
#include "Enemy.h"

//USING STATEMENTS
using namespace std;

//STATIC VARIABLES


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Main Game Window");
    window.setKeyRepeatEnabled(false);

    Player player(sf::Vector2f(32, 32), sf::Vector2f(400, 400));
    Enemy enemy(sf::Vector2f(32, 32), sf::Vector2f(600, 200));

    sf::Clock fpsClock;

    int fpsCounter = 0;
    int frameCounter = 0;    

    Util::initTextBoxes();
    player.Load();   
    enemy.Load();
    

    while (window.isOpen())
    {
        sf::Event closeEvent;
        while (window.pollEvent(closeEvent)) {
            if (closeEvent.type == sf::Event::Closed) {
                window.close();
            }
        }

        player.Update(frameCounter, window);
        enemy.Update(frameCounter, player);

        window.clear();
        player.Draw(window);
        enemy.Draw(window);
        Util::showFPS(fpsClock, fpsCounter, window);
        window.display();
        
        fpsCounter++;
        frameCounter++;
    }

    return 0;
}  
