/*
** EPITECH PROJECT, 2025
** Src/SFMLDisplay
** File description:
** SFMLDisplay
*/

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

#include "SFMLDisplay.hpp"
#include "Display/SFML/Box.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/Chart.hpp"
#include "Display/SFML/ClockDisplay.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/TextBox.hpp"

Krell::SFMLDisplay::SFMLDisplay() : IDisplay(), _isRunning(false), _refreshDelay(100)
{
}

Krell::SFMLDisplay::~SFMLDisplay()
{
    if (_isRunning)
    {
        stop();
    }
}

void Krell::SFMLDisplay::start()
{
    _window.create(sf::VideoMode(1600, 1024), "MyGKrellm");
    _window.setFramerateLimit(60);
    _isRunning = true;
}

void Krell::SFMLDisplay::refresh()
{
    static sf::Clock clock;

    _window.clear(BG_COLOR);

    if (clock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        clock.restart();
        for (const auto &[name, module] : _modules)
        {
            module->refresh();
        }
        refresh_all();
    }

    Display::Container container(sf::Vector2f(0, 0), sf::Vector2f(200, 100));
    Display::Box box(container.getSize());
    Display::ProgressBar progressBar(sf::Vector2f(200, 50));

    sf::Font font;
    if (!font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font\n";
    }

    // CPU Usage
    Display::TextBox cpuTextBox(sf::Vector2f(20, 20), "CPU Usage", font);
    cpuTextBox.setPosition(sf::Vector2f(container.getPosition().x + 100, container.getPosition().y + 70));
    cpuTextBox.draw(_window);
    progressBar.setProgress(_modules["cpu_usage"]->getValue("usedPercent"));
    progressBar.setPosition(sf::Vector2f(container.getPosition().x + 100, container.getPosition().y + 100));
    progressBar.draw(_window);

    // Memory Usage
    container.setPosition(sf::Vector2f(200, 0));

    Display::TextBox ramTextBox(sf::Vector2f(20, 20), "RAM Usage", font);
    ramTextBox.setPosition(sf::Vector2f(400, 70));
    ramTextBox.draw(_window);
    progressBar.setProgress(_modules["mem"]->getValue("usedPercent"));
    progressBar.setPosition(sf::Vector2f(400, 100));
    progressBar.draw(_window);

    // Refresh Delay
    Display::TextBox delayTextBox(sf::Vector2f(20, 20), "Refresh Delay: " + std::to_string(_refreshDelay) + "ms", font);
    delayTextBox.setPosition(sf::Vector2f(600, 70));
    delayTextBox.draw(_window);

    container.setPosition(sf::Vector2f(400, 300));
    Display::Chart chart(container.getSize());
    chart.setPosition(container.getPosition());
    chart.setData({10, 20, 30, 40, 50, 20, 10, 2, 15, 80});
    chart.draw(_window);

    Display::ClockDisplay clockDisplay(sf::Vector2f(200, 50), sf::Vector2f(1500, 0));
    clockDisplay.update();
    clockDisplay.draw(_window);

    _window.display();
}

void Krell::SFMLDisplay::stop()
{
    _window.close();
    _isRunning = false;
}

void Krell::SFMLDisplay::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _isRunning = false;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                _refreshDelay = std::min(10000, _refreshDelay + 100);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                _refreshDelay = std::max(100, _refreshDelay - 100);
            }
        }
    }
}

bool Krell::SFMLDisplay::isRunning() const
{
    return _isRunning;
}
