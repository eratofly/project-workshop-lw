#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rectangle and circle");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({60, 165});
    shape1.setPosition({20, 20});
    shape1.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(shape1);

    sf::CircleShape shape2(20);
    shape2.setPosition({30, 35});
    shape2.setFillColor(sf::Color::Green);
    window.draw(shape2);

    sf::CircleShape shape3(20);
    shape3.setPosition({30, 85});
    shape3.setFillColor(sf::Color(0xE5, 0xEC, 0x16));
    window.draw(shape3);

    sf::CircleShape shape4(20);
    shape4.setPosition({30, 135});
    shape4.setFillColor(sf::Color::Red);
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(3));
}