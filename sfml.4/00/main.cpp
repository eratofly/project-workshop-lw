#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * (float)cos(angle),
        radius * (float)sin(angle)};
}

float toDegress(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateArrow()
{
}

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    arrow.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    arrow.setOutlineThickness(5);
    arrow.setPosition({200, 120});
    arrow.setPointCount(7);
    arrow.setPoint(0, {50, 0});
    arrow.setPoint(1, {0, -30});
    arrow.setPoint(2, {0, -15});
    arrow.setPoint(3, {-50, -15});
    arrow.setPoint(4, {-50, 15});
    arrow.setPoint(5, {0, 15});
    arrow.setPoint(6, {0, 30});
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void update()
{
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Yellow arrow", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    initArrow(arrow);

    while (window.isOpen())
    {
        pollEvents(window);
        update();
        redrawFrame(window, arrow);
    }
}