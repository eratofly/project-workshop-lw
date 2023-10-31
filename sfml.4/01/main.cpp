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

float onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

sf::Vector2f getDirection(sf::Vector2f delta)
{
    float absDelta = std::sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    return {delta.x / absDelta, delta.y / absDelta};
}

void updateArrow(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, sf::Clock &clock)
{
    float speedAngle = 900.f;
    float speedDirection = 200.f;
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    const sf::Vector2f position = arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    angle = toDegress(angle);
    float arrowAngle = arrow.getRotation();
    if (angle < 0)
    {
        angle += 360;
    }
    if (std::abs(arrowAngle - angle) > std::abs(arrowAngle - angle - 360))
    {
        angle += 360;
    }
    const float dt = clock.restart().asSeconds();

    if (arrowAngle < angle)
        arrow.rotate(speedAngle * dt);
    else if (arrowAngle > angle)
        arrow.rotate(-speedAngle * dt);

    float distance = speedDirection * dt;
    arrow.setPosition(position + distance * getDirection(delta));
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
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

    sf::Clock clock;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Yellow arrow", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateArrow(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    }
}