/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** Box
*/

#include <SFML/Graphics.hpp>
#include <string>

#include "SFMLDisplay.hpp"
#include "Display/SFML/Box.hpp"

namespace Display
{
    Box::Box(sf::Vector2f size)
    {
        _rectangle.setSize(size);
        _rectangle.setFillColor(BOX_COLOR);
        // _rectangle.setOutlineThickness(2);
        // _rectangle.setOutlineColor(sf::Color::Black);
    }

    void Box::setPosition(sf::Vector2f position)
    {
        _rectangle.setPosition(position);
    }

    void Box::draw(sf::RenderWindow &window)
    {
        window.draw(_rectangle);
    }
}
