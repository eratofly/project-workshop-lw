#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegress(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{

    mousePosition = {float(event.x), float(event.y)};
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

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &clock)
{
    float speed = 150.f;
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = atan2(delta.y, delta.x);
    angle = toDegress(angle);
    float pointerAngle = pointer.getRotation();
    if (angle < 0)
    {
        angle += 360;
    }
    if (std::abs(pointerAngle - angle) > std::abs(pointerAngle - angle - 360))
    {
        angle += 360;
    }
    const float dt = clock.restart().asSeconds();

    if (pointerAngle < angle)
        pointer.rotate(speed * dt);
    else if (pointerAngle > angle)
        pointer.rotate(-speed * dt);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
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
        "Prints mouse events to terminal", sf::Style::Default, settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock);
        redrawFrame(window, pointer);
    }
}
