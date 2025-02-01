/*
** EPITECH PROJECT, 2025
** src/Display/SFML/Container
** File description:
** Container
*/

#include "SFMLDisplay.hpp"

#include "Display/SFML/Container.hpp"

namespace Display
{
    void Container::setPosition(const sf::Vector2f &position)
    {
        _position = position;
        _rectangle.setPosition(_position);
    }

    void Container::setSize(const sf::Vector2f &size)
    {
        _size = size;
        _rectangle.setSize(_size);
    }

    const sf::Vector2f &Container::getPosition() const
    {
        return _position;
    }

    const sf::Vector2f &Container::getSize() const
    {
        return _size;
    }

    void Container::draw(sf::RenderWindow &window)
    {
        window.draw(_rectangle);
    }
}
