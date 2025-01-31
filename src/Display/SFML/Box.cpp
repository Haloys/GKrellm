/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** Box
*/

#include <SFML/Graphics.hpp>
#include <string>

#include "Display/SFML/Box.hpp"

namespace Box
{
    Box::Box(sf::Vector2f size)
    {
        _rectangle.setSize(size);
        _rectangle.setFillColor(sf::Color(50, 50, 50)); // #323232 in RGB
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
