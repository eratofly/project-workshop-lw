#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

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

sf::Sprite initSprite(sf::Texture &texture, const std::string &path)
{
    if (!texture.loadFromFile(path))
    {
        exit(0);
    }
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
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

void updateSprite(const sf::Vector2f &mousePosition, sf::Sprite &sprite, sf::Clock &clock)
{
    float speedAngle = 900.f;
    float speedDirection = 200.f;
    const sf::Vector2f delta = mousePosition - sprite.getPosition();
    const sf::Vector2f position = sprite.getPosition();
    float angle = atan2(delta.y, delta.x);
    angle = toDegress(angle);
    float spriteAngle = sprite.getRotation();
    if (angle < 0)
    {
        angle += 360;
    }
    if (std::abs(spriteAngle - angle) > std::abs(spriteAngle - angle - 360))
    {
        angle += 360;
    }
    const float dt = clock.restart().asSeconds();

    if (spriteAngle < angle)
        sprite.rotate(speedAngle * dt);
    else if (spriteAngle > angle)
        sprite.rotate(-speedAngle * dt);

    float distance = speedDirection * dt;
    sprite.setPosition(position + distance * getDirection(delta));
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

void redrawFrame(sf::RenderWindow &window, sf::Sprite &sprite)
{
    window.clear(sf::Color(0x4F, 0x4F, 0xFF));
    window.draw(sprite);
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
        "The cat follows the mouse", sf::Style::Default, settings);

    sf::Vector2f mousePosition;

    sf::Texture texture;
    const std::string path = "D:/project-workshop-lw/cat.png";

    sf::Sprite sprite = initSprite(texture, path);
    sprite.setPosition({400, 300});

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        redrawFrame(window, sprite);
    }
}