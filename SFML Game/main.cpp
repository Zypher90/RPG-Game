#include <SFML/Graphics.hpp>
#include<iostream>

//USING STATEMENTS
using namespace std;

//STATIC VARIABLES
static int baseVelocity = 0;
static int fps;
static float elapsedTimeCheck;

//FUNCTION SIGNATURES
static bool anyKeyPressed();
sf::Vector2f normalize(sf::Vector2f& vector);
sf::Vector2i normalize_int(sf::Vector2i vector);

int main()
{
    //------------------------------------------------------INITIALIZE--------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(800, 800), "Main Game Window");
    window.setKeyRepeatEnabled(false);

    sf::Texture playerIdleTexture;
    sf::Texture playerWalkTexture;
    sf::Texture bulletTexture;

    sf::Sprite player;
    std::vector<sf::Sprite> bulletVec;

    sf::Clock gameClock;

    sf::Text fpsCounter;

    sf::Font helvetica;

    sf::Vector2i characterPixelResolution(64, 64);

    int walkLoopIndexHorizontal = 0;
    int walkLoopIndexVertical = 0;

    int idleLoopIndexHorizontal = 0;
    int idleLoopIndexVertical = 0;

    int frameConsolidationCounter = 0;
    int frameElapsedCounter = 0;

    std::string fpsCounterConcat;
    //------------------------------------------------------INITIALIZE--------------------------------------------------------------
    



    //------------------------------------------------------LOAD--------------------------------------------------------------

    //PLAYER IDLE TEXTURE
    if (!playerIdleTexture.loadFromFile("Assets/Spritesheets/Player-Male/Unarmed_Idle/Unarmed_Idle_full.png"))
        cout << "Coudln't load player idle spritesheet" << endl;

    //PLAYER WALK TEXTURE
    if (!playerWalkTexture.loadFromFile("Assets/Spritesheets/Player-Male/Unarmed_Walk/Unarmed_Walk_full.png"))
        cout << "Couldn't load player walk spritesheet" << endl;

    //HELVETICA FONT
    if (!helvetica.loadFromFile("Assets/Fonts/Helvetica/Helvetica.ttf"))
        cout << "Couldn't load Helvetica font" << endl;
    
    if (!bulletTexture.loadFromFile("Assets/Sprites/playerbullet.png"))
        cout << "Couldn't load bullet texture";

    //------------------------------------------------------LOAD--------------------------------------------------------------



    //------------------------------------------------------ASSIGNMENTS--------------------------------------------------------

    fpsCounter.setFont(helvetica);
    fpsCounter.setCharacterSize(20);
    fpsCounter.setFillColor(sf::Color::White);
    fpsCounter.setStyle(sf::Text::Bold);
    fpsCounter.setPosition(sf::Vector2f(700, 0));

    //------------------------------------------------------ASSIGNMENTS--------------------------------------------------------



    //------------------------------------------------------GAME LOOP--------------------------------------------------------------

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
    


    //------------------------------------------------------UPDATE--------------------------------------------------------------


        //======================================================== IDLE LOOP =====================================================
        //(scuffed)
        sf::Event isKeyPressed;


        if (anyKeyPressed) {
            //cout << "any key not pressed" << endl;
            player.setTexture(playerIdleTexture);
            player.setTextureRect(sf::IntRect(sf::Vector2i(idleLoopIndexHorizontal * 64, idleLoopIndexVertical * 64), characterPixelResolution));
            player.setScale(sf::Vector2f(3, 3));
        }
        //======================================================== IDLE LOOP =====================================================


        //======================================================== WALK LOOP =====================================================
        sf::Vector2f playerPosition(player.getPosition());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.setTexture(playerWalkTexture);
            //walkLoopIndexHorizontal = 0;
            walkLoopIndexVertical = 3;
            player.setPosition(playerPosition + sf::Vector2f(0, -0.10));
            player.setTextureRect(sf::IntRect(sf::Vector2i(walkLoopIndexHorizontal * 64, walkLoopIndexVertical * 64), characterPixelResolution));
            player.setScale(sf::Vector2f(3, 3));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.setTexture(playerWalkTexture);
            //walkLoopIndexHorizontal = 0;
            walkLoopIndexVertical = 0;
            player.setPosition(playerPosition + sf::Vector2f(0, 0.10));
            player.setTextureRect(sf::IntRect(sf::Vector2i(walkLoopIndexHorizontal * 64, walkLoopIndexVertical * 64), characterPixelResolution));
            player.setScale(sf::Vector2f(3, 3));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.setTexture(playerWalkTexture);
            //walkLoopIndexHorizontal = 0;
            walkLoopIndexVertical = 1;
            player.setPosition(playerPosition + sf::Vector2f(-0.10, 0));
            player.setTextureRect(sf::IntRect(sf::Vector2i(walkLoopIndexHorizontal * 64, walkLoopIndexVertical * 64), characterPixelResolution));
            player.setScale(sf::Vector2f(3, 3));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.setTexture(playerWalkTexture);
            //walkLoopIndexHorizontal = 0;
            walkLoopIndexVertical = 2;
            player.setPosition(playerPosition + sf::Vector2f(0.10, 0));
            player.setTextureRect(sf::IntRect(sf::Vector2i(walkLoopIndexHorizontal * 64, walkLoopIndexVertical * 64), characterPixelResolution));
            player.setScale(sf::Vector2f(3, 3));
        }
        //======================================================== WALK LOOP =====================================================
        

        //======================================================== HANDLING BULLETS =====================================================
        sf::Vector2f heading = sf::Vector2f(normalize_int(sf::Mouse::getPosition(window)));

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            bulletVec.push_back(sf::Sprite(bulletTexture));
            cout << "done" << endl;
            bulletVec[bulletVec.size() - 1].setPosition(playerPosition);
            bulletVec[bulletVec.size() - 1].setOrigin(311, 460);
            bulletVec[bulletVec.size() - 1].setRotation(atan(heading.y / heading.x));
            bulletVec[bulletVec.size() - 1].setPosition(bulletVec[bulletVec.size() - 1].getPosition() + heading);
            float xpos = bulletVec[bulletVec.size() - 1].getPosition().x;
            float ypos = bulletVec[bulletVec.size() - 1].getPosition().y;
            cout << xpos << "," << ypos << endl;
        }


        //======================================================== HANDLING BULLETS =====================================================

    //------------------------------------------------------UPDATE--------------------------------------------------------------


    //------------------------------------------------------DRAW--------------------------------------------------------------
        window.clear();
        window.draw(player);
        window.draw(fpsCounter);
        
        for (int i = 0; i < bulletVec.size(); i++) {
            window.draw(bulletVec[i]);
        }

        window.display();
    //------------------------------------------------------DRAW--------------------------------------------------------------




        //================================ FPS CONSOLIDATION AND INDEX UPDATES ==============================================
        frameConsolidationCounter++;
        frameElapsedCounter++;
        //WALK 
        if (frameConsolidationCounter % 400 == 0) {
            walkLoopIndexHorizontal++;
        }
        if (walkLoopIndexHorizontal == 5) {
            walkLoopIndexHorizontal = 0;
        }
        //WALK

        //IDLE
        if (frameConsolidationCounter % 1200 == 0) {
            idleLoopIndexHorizontal++;
        }
        if (idleLoopIndexHorizontal == 4) {
            idleLoopIndexHorizontal = 0;
        }
        //IDLE

        //RUN

        //RUN

        //================================ FPS CONSOLIDATION AND INDEX UPDATES ==============================================



    }

    //------------------------------------------------------GAME LOOP--------------------------------------------------------------
    
    return 0;
}  


//=========================================================FUNCTIONS==============================================================

static bool anyKeyPressed() {
    for (int i = -1; i < sf::Keyboard::KeyCount; ++i) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
        return true;
    }
    return false;
}


sf::Vector2f normalize(sf::Vector2f& vector) {
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
//=========================================================FUNCTIONS==============================================================