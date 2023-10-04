#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Simple Event Loop");
    sf::Clock clock;

    const sf::Vector2f positionStart = {10, 350};

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    ball.setPosition(positionStart);

    float time = 0;
    float speedX = 100.f;

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
        time += dt;

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        sf::Vector2f position = ball.getPosition();
        position.x += speedX * dt;

        const float wavePhase = time * float(2 * M_PI);
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {0, y};

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        ball.setPosition({position.x, offset.y + positionStart.y});

        window.clear();
        window.draw(ball);
        window.display();
    }
}