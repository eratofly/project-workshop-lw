#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr int pointCount = 200;
    constexpr float radiusTrack = 100;
    constexpr float speedAngle = 15;
    float angleTrack = 0;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Ellipse",
        sf::Style::Default, settings);

    sf::ConvexShape ellipse;
    sf::Vector2f position = {400, 300};
    ellipse.setPosition(position);
    ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = 200 * sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{
            radius * std::sin(angle),
            radius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        float deltaAngle = float(speedAngle * dt) / float(2 * M_PI);
        angleTrack += deltaAngle;
        sf::Vector2f offset = sf::Vector2f{
            radiusTrack * std::sin(angleTrack),
            radiusTrack * std::cos(angleTrack)};
        ellipse.setPosition(position + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}