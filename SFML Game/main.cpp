#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "This is a window");
    sf::CircleShape circle(100.f);
    circle.setOrigin(100, 100);
    circle.setPosition(sf::Vector2f(200, 200));
    circle.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Green);
        window.draw(circle);
        window.display();
    }

    return 0;
}  