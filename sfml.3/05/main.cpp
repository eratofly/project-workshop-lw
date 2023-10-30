#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

struct Eye
{
    sf::ConvexShape pupil;
    sf::ConvexShape eyeball;
    sf::Vector2f position;
    float pupilRotation = 0;
};

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

void updateEyeElements(Eye &eye)
{
    eye.eyeball.setPosition(eye.position);

    const sf::Vector2f pupilRotationOffset = toEuclidean(40, eye.pupilRotation);
    eye.pupil.setPosition(eye.position + pupilRotationOffset);
}

void initEllipse(sf::ConvexShape &ellipse, int pointCount, sf::Vector2f ellipseRadius, sf::Color color)
{
    ellipse.setFillColor(color);
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {

        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }
}

void initEye(Eye &eye, sf::Vector2f position)
{
    eye.position = position;

    int pointCount = 200;
    const sf::Vector2f eyeballRadius = {60.f, 120.f};
    const sf::Color eyeballColor = sf::Color(0xFF, 0xFF, 0xFF);

    initEllipse(eye.eyeball, pointCount, eyeballRadius, eyeballColor);

    const sf::Vector2f pupilRadius = {15.f, 30.f};
    const sf::Color pupilColor = sf::Color(0x00, 0x00, 0x00);

    initEllipse(eye.pupil, pointCount, pupilRadius, pupilColor);

    updateEyeElements(eye);
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

void update(const sf::Vector2f &mousePosition, Eye &eye)
{
    const sf::Vector2f delta = mousePosition - eye.position;
    eye.pupilRotation = atan2(delta.y, delta.x);
    updateEyeElements(eye);
}

void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye)
{
    window.clear();
    window.draw(leftEye.eyeball);
    window.draw(leftEye.pupil);
    window.draw(rightEye.eyeball);
    window.draw(rightEye.pupil);
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
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye leftEye;
    Eye rightEye;

    sf::Vector2f mousePosition;

    initEye(leftEye, {300, WINDOW_HEIGHT / 2});
    initEye(rightEye, {500, WINDOW_HEIGHT / 2});

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye);
        update(mousePosition, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}