#include <SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"

//USING STATEMENTS
using namespace std;

//STATIC VARIABLES
static int baseVelocity = 0;
static int fps;
static float elapsedTimeCheck;

//FUNCTION SIGNATURES
static bool anyKeyPressed();
static bool walkTriggerActivated();
sf::Vector2f normalize(sf::Vector2f vector);
sf::Vector2i normalize_int(sf::Vector2i vector);

int main()
{
    //------------------------------------------------------INITIALIZE--------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(800, 800), "Main Game Window");
    window.setKeyRepeatEnabled(false);

    Player player;
    player.setPosition(sf::Vector2f(0, 0));

    sf::Texture bulletTexture;

    std::vector<sf::RectangleShape> bulletVec;

    sf::Clock gameClock;

    sf::Text fpsCounter;

    sf::Font helvetica;

    sf::Vector2i characterPixelResolution(64, 64);


    int frameConsolidationCounter = 0;
    int frameElapsedCounter = 0;

    std::string fpsCounterConcat;
    
    sf::Vector2f bulletHeading;
    //------------------------------------------------------INITIALIZE--------------------------------------------------------------
    



    //--------------------------------------------LOAD-----------------------------------------------------

    player.Load();

    //HELVETICA FONT
    if (!helvetica.loadFromFile("Assets/Fonts/Helvetica/Helvetica.ttf"))
        cout << "Couldn't load Helvetica font" << endl;

    //---------------------------------------LOAD------------------------------------------



    //-----------------------------------------ASSIGNMENTS------------------------------------------------

    fpsCounter.setFont(helvetica);
    fpsCounter.setCharacterSize(20);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setStyle(sf::Text::Bold);
    fpsCounter.setPosition(sf::Vector2f(700, 0));

    //---------------------------------------------ASSIGNMENTS------------------------------------------------



    //----------------------------------------------GAME LOOP--------------------------------------------------------------

    while (window.isOpen())
    {


        //WINDOW CLOSE
        sf::Event windowCloseIndicator;
        while (window.pollEvent(windowCloseIndicator))
        {
            if (windowCloseIndicator.type == sf::Event::Closed)
                window.close();
        }
        //WINDOW CLOSE

        elapsedTimeCheck = gameClock.getElapsedTime().asSeconds();

        //CALCULATE FPS
        if(elapsedTimeCheck>0.24 && elapsedTimeCheck<0.26){
            gameClock.restart();
            fps = frameElapsedCounter * 4;
            frameElapsedCounter = 0;
            fpsCounter.setString("FPS:"+to_string(fps));
        }
        //CALCULATE FPS
    


    //-------------------------------------------------- UPDATE-----------------------------------------------------

        player.Update();

        //========================================= HANDLING BULLETS ==============================================

        

        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //    bulletVec.push_back(sf::RectangleShape(sf::Vector2f(2, 4)));
        //    bulletVec[bulletVec.size() - 1].setPosition(player.getPosition());
        //    bulletHeading = normalize(sf::Vector2f(sf::Mouse::getPosition()) - player.getPosition());
        //    bulletHeading.x = bulletHeading.x * 200;
        //    bulletHeading.y = bulletHeading.y * 200;
        //    //bulletVec[bulletVec.size() - 1].setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        //}

        /*for (int i = 0; i < bulletVec.size(); i++) {
            bulletVec[i].setPosition(bulletVec[i].getPosition() + bulletHeading);
        }*/
        //======================================================== HANDLING BULLETS =====================================================

    //------------------------------------------------UPDATE--------------------------------------------------------


    //------------------------------------------------DRAW------------------------------------------
        window.clear();
        player.Draw(window);
        window.draw(fpsCounter);
        
        for (int i = 0; i < bulletVec.size(); i++) {
            window.draw(bulletVec[i]);
        }

        window.display();
    //------------------------------------------------DRAW-------------------------------------------




        //================================ FPS CONSOLIDATION AND INDEX UPDATES ==============================================
        frameConsolidationCounter++;
        frameElapsedCounter++;
        //WALK 
        
        //IDLE

        //RUN

        //RUN

        //================================ FPS CONSOLIDATION AND INDEX UPDATES ==============================================



    }

    //------------------------------------------------------GAME LOOP--------------------------------------------------------------
    
    return 0;
}  


//=========================================================FUNCTIONS==============================================================

//static bool anyKeyPressed() {
//    for (int i = -1; i < sf::Keyboard::KeyCount; ++i) {
//        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
//        return true;
//    }
//    return false;
//}


sf::Vector2f normalize(sf::Vector2f vector) {
    int m = vector.x * vector.x + vector.y * vector.y;
    sf::Vector2f unitVector;
    unitVector.x = vector.x / m;
    unitVector.y = vector.y / m;

    return unitVector;
}

sf::Vector2i normalize_int(sf::Vector2i vector) {
    int m = vector.x * vector.x + vector.y * vector.y;
    sf::Vector2i unitVector;
    unitVector.x = vector.x / m;
    unitVector.y = vector.y / m;

    return unitVector;
}

static bool anyKeyPressed() {
    for (int i = -1; i < sf::Keyboard::KeyCount; ++i) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
            return true;
    }
    return false;
}

//=========================================================FUNCTIONS==============================================================