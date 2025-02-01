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
#include "Utils.hpp"
// #include "Display/SFML/Box.hpp"
// #include "Display/SFML/ProgressBar.hpp"
// #include "Display/SFML/Container.hpp"
// #include "Display/SFML/Chart.hpp"
#include "Display/SFML/ClockDisplay.hpp"
#include "Display/SFML/TextBox.hpp"
// #include "IModule.hpp"

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
    getWindow().create(sf::VideoMode(1600, 1024), "MyGKrellm");
    getWindow().setFramerateLimit(60);
    _isRunning = true;
    if (!getFont().loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font\n";
    }
}

void Krell::SFMLDisplay::drawModule()
{

}

void Krell::SFMLDisplay::refresh()
{
    getWindow().clear(BG_COLOR);

    if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        for (const auto &[name, module] : _modules)
        {
            module->refresh();
        }
        refresh_all();
    }

    for (const auto &[name, module] : _modules)
    {
        module->drawModule(*this);
    }

    // Refresh Delay
    Display::TextBox delayTextBox(sf::Vector2f(20, 20), "Refresh Delay: " + std::to_string(_refreshDelay) + "ms", getFont());
    delayTextBox.setPosition(sf::Vector2f(700, 70));
    delayTextBox.draw(getWindow());

    Display::ClockDisplay clockDisplay(sf::Vector2f(200, 50), sf::Vector2f(1500, 0));
    clockDisplay.update();
    clockDisplay.draw(getWindow());
    if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        _delayClock.restart();
    }
    getWindow().display();
}

void Krell::SFMLDisplay::stop()
{
    getWindow().close();
    _isRunning = false;
}

void Krell::SFMLDisplay::handleEvents()
{
    sf::Event event;
    while (getWindow().pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _isRunning = false;
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Up)
            {
                _refreshDelay = std::min(10000, _refreshDelay + 100);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                _refreshDelay = std::max(100, _refreshDelay - 100);
            }
            break;
        default:
            break;
        }
    }
}

bool Krell::SFMLDisplay::isRunning() const
{
    return _isRunning;
}
