/*
** EPITECH PROJECT, 2025
** src/Display/SFML/Container
** File description:
** Container
*/

#include "SFMLDisplay.hpp"

#include "Display/SFML/Container.hpp"

void Display::Container::setPosition(const sf::Vector2f &position)
{
    _position = position;
    _rectangle.setPosition(_position);
}

void Display::Container::setSize(const sf::Vector2f &size)
{
    _size = size;
    _rectangle.setSize(_size);
}

const sf::Vector2f &Display::Container::getPosition() const
{
    return _position;
}

const sf::Vector2f &Display::Container::getSize() const
{
    return _size;
}

void Display::Container::draw(sf::RenderWindow &window)
{
    window.draw(_rectangle);
}
