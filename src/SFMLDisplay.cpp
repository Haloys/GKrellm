/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/src/main
** File description:
** central file
*/

#include "SFMLDisplay.hpp"

Krell::SFMLDisplay::SFMLDisplay() : _isRunning(false)
{

}

Krell::SFMLDisplay::~SFMLDisplay()
{
    if (_isRunning) {
        stop();
    }
}

void Krell::SFMLDisplay::start()
{
    _window.create(sf::VideoMode(800, 600), "MyGKrellm");
    _window.setFramerateLimit(60);
    _isRunning = true;
}

void Krell::SFMLDisplay::refresh()
{
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