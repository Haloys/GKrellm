/*
** EPITECH PROJECT, 2025
** src/Display/SFML/ClockDisplay
** File description:
** ClockDisplay
*/

#include <ctime>

#include "SFMLDisplay.hpp"
#include "Display/SFML/ClockDisplay.hpp"

namespace Display
{
    ClockDisplay::ClockDisplay(const sf::Vector2f &size, const sf::Vector2f &position)
        : _box(size * 0.5f), _position(position)
    {
        if (!_font.loadFromFile(FONT_PATH))
        {
            return;
        }
        _text.setFont(_font);
        _text.setCharacterSize(24);
        _text.setFillColor(sf::Color::White);
        _text.setPosition(_position);
    }

    void ClockDisplay::update()
    {
        std::time_t now = std::time(nullptr);
        std::tm *localTime = std::localtime(&now);
        char buffer[10];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
        _text.setString(buffer);
    }

    void ClockDisplay::draw(sf::RenderWindow &window)
    {
        _box.setPosition(_position);
        _box.draw(window);
        window.draw(_text);
    }
}
