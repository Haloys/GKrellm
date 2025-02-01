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


Krell::SFMLDisplay::SFMLDisplay() : _isRunning(false), IDisplay() {}

Krell::SFMLDisplay::~SFMLDisplay()
{
    if (_isRunning) {
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
    _window.clear(BG_COLOR);

    for (const auto& [name, module] : _modules) {
        module->refresh();
    }


    refresh_all();

    Display::Container container(sf::Vector2f(100, 100), sf::Vector2f(200, 100));
    Display::Box box(container.getSize());
    Display::ProgressBar progressBar(container.getSize());

    // CPU Usage
    box.setPosition(container.getPosition());
    box.draw(_window);
    progressBar.setProgress(_modules["cpu_usage"]->getValue("usedPercent"));
    progressBar.setPosition(container.getPosition());
    progressBar.draw(_window);

    container.setPosition(sf::Vector2f(400, 100));
    box.setPosition(container.getPosition());
    box.draw(_window);

    container.setPosition(sf::Vector2f(700, 100));
    box.setPosition(container.getPosition());
    box.draw(_window);

    container.setPosition(sf::Vector2f(1000, 100));
    box.setPosition(container.getPosition());
    box.draw(_window);

    container.setPosition(sf::Vector2f(1300, 100));
    box.setPosition(container.getPosition());
    box.draw(_window);

    container.setPosition(sf::Vector2f(100, 300));
    box.setPosition(container.getPosition());
    box.draw(_window);

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
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _isRunning = false;
        }
    }
}

bool Krell::SFMLDisplay::isRunning() const
{
    return _isRunning;
}
