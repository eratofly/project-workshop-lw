#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void drawCircle(sf::CircleShape &name, float radius, float x, float y, sf::Color color)
{
    name.setRadius(radius);
    name.setPosition({x, y});
    name.setFillColor(color);
}

void drawRect(sf::RectangleShape &name, float width, float height, float x, float y, sf::Color color, float rotationAngle = 0)
{
    name.setSize({width, height});
    name.setPosition({x, y});
    name.setRotation(rotationAngle);
    name.setFillColor(color);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Convex Shape");
    window.clear();

    sf::RectangleShape basement;
    drawRect(basement, 450, 300, 100, 340, sf::Color(0x8B, 0x45, 0x13));
    window.draw(basement);

    sf::RectangleShape door;
    drawRect(door, 70, 200, 140, 440, sf::Color(0x30, 0x2B, 0x2B));
    window.draw(door);

    sf::ConvexShape root;
    root.setFillColor(sf::Color(0x66, 0x1C, 0x1C));
    root.setPosition({100, 220});
    root.setPointCount(4);
    root.setPoint(0, {-50, 120});
    root.setPoint(1, {500, 120});
    root.setPoint(2, {350, 0});
    root.setPoint(3, {100, 0});
    window.draw(root);

    sf::CircleShape smoke1;
    drawCircle(smoke1, 20, 408, 123, sf::Color(0xB3, 0xAF, 0xAF));
    window.draw(smoke1);

    sf::CircleShape smoke2;
    drawCircle(smoke2, 25, 415, 90, sf::Color(0xB3, 0xAF, 0xAF));
    window.draw(smoke2);

    sf::CircleShape smoke3;
    drawCircle(smoke3, 30, 430, 50, sf::Color(0xB3, 0xAF, 0xAF));
    window.draw(smoke3);

    sf::CircleShape smoke4;
    drawCircle(smoke4, 30, 440, 15, sf::Color(0xB3, 0xAF, 0xAF));
    window.draw(smoke4);

    sf::RectangleShape chimney1;
    drawRect(chimney1, 40, 70, 395, 205, sf::Color(0x5B, 0x51, 0x51));
    window.draw(chimney1);

    sf::RectangleShape chimney2;
    drawRect(chimney2, 70, 50, 380, 160, sf::Color(0x5B, 0x51, 0x51));
    window.draw(chimney2);

    window.display();

    sf::sleep(sf::seconds(2));
}