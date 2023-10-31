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
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    return sprite;
}

float onMouseReleased(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

sf::Vector2f getDirection(sf::Vector2f delta)
{
    float absDelta = std::sqrt(pow(delta.x, 2) + pow(delta.y, 2));
    return {delta.x / absDelta, delta.y / absDelta};
}

void updateSpriteCat(const sf::Vector2f &mousePosition, sf::Sprite &sprite, sf::Clock &clock)
{
    float speedDirection = 200.f;
    const sf::Vector2f delta = mousePosition - sprite.getPosition();
    const sf::Vector2f position = sprite.getPosition();
    const float dt = clock.restart().asSeconds();

    if (mousePosition.x < position.x)
    {
        sprite.setScale(-1, 1);
    }
    else
    {
        sprite.setScale(1, 1);
    }
    float distance = speedDirection * dt;
    sprite.setPosition(position + distance * getDirection(delta));
}

void updateSpritePointer(const sf::Vector2f &mousePosition, sf::Sprite &sprite)
{
    sprite.setPosition(mousePosition);
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
        case sf::Event::MouseButtonReleased:
            onMouseReleased(event.mouseButton, mousePosition);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &spriteCat, sf::Sprite &spritePointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(spritePointer);
    window.draw(spriteCat);
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

    sf::Texture textureCat;
    sf::Texture texturePointer;
    const std::string pathCat = "D:/project-workshop-lw/cat.png"; // у меня получается написать относительный путь, кидает ошибку
    const std::string pathPointer = "D:/project-workshop-lw/red_pointer.png";

    sf::Sprite cat = initSprite(textureCat, pathCat);
    cat.setPosition({400, 300});

    sf::Sprite pointer = initSprite(texturePointer, pathPointer);
    pointer.setPosition({400, 300});

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateSpriteCat(mousePosition, cat, clock);
        updateSpritePointer(mousePosition, pointer);
        redrawFrame(window, cat, pointer);
    }
}