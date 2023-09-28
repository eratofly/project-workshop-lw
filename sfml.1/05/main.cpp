#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void drawRect(sf::RectangleShape &name, float width, float height, float x, float y, sf::Color color, float rotationAngle = 0)
{
    name.setSize({width, height});
    name.setPosition({x, y});
    name.setRotation(rotationAngle);
    name.setFillColor(color);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Convex Shape");
    window.clear();

    sf::RectangleShape wO1;
    drawRect(wO1, 100, 30, 30, 120, sf::Color::Red);
    window.draw(wO1);

    sf::RectangleShape wO2;
    drawRect(wO2, 30, 200, 30, 150, sf::Color::Red);
    window.draw(wO2);

    sf::RectangleShape wO3;
    drawRect(wO3, 100, 30, 30, 320, sf::Color::Red);
    window.draw(wO3);

    sf::RectangleShape wO4;
    drawRect(wO4, 30, 200, 100, 130, sf::Color::Red);
    window.draw(wO4);

    sf::RectangleShape wD1;
    drawRect(wD1, 100, 30, 160, 120, sf::Color::Blue);
    window.draw(wD1);

    sf::RectangleShape wD2;
    drawRect(wD2, 30, 200, 160, 150, sf::Color::Blue);
    window.draw(wD2);

    sf::RectangleShape wD3;
    drawRect(wD3, 100, 30, 160, 320, sf::Color::Blue);
    window.draw(wD3);

    sf::RectangleShape wD4;
    drawRect(wD4, 30, 200, 260, 135, sf::Color::Blue);
    window.draw(wD4);

    sf::RectangleShape wC1;
    drawRect(wC1, 100, 30, 320, 120, sf::Color::Green);
    window.draw(wC1);

    sf::RectangleShape wC2;
    drawRect(wC2, 30, 100, 320, 150, sf::Color::Green);
    window.draw(wC2);

    sf::RectangleShape wC3;
    drawRect(wC3, 100, 30, 320, 320, sf::Color::Green);
    window.draw(wC3);

    sf::RectangleShape wC4;
    drawRect(wC4, 100, 30, 320, 220, sf::Color::Green);
    window.draw(wC4);

    sf::RectangleShape wC5;
    drawRect(wC5, 30, 100, 390, 220, sf::Color::Green);
    window.draw(wC5);

    window.display();

    sf::sleep(sf::seconds(2));
}