/*
** EPITECH PROJECT, 2025
** src/Display/SFML/Box
** File description:
** Box
*/

#include <SFML/Graphics.hpp>
#include <string>

#include "SFMLDisplay.hpp"
#include "Display/SFML/Box.hpp"

Display::Box::Box(sf::Vector2f size)
{
    _rectangle.setSize(size);
    _rectangle.setFillColor(BOX_COLOR);
    // _rectangle.setOutlineThickness(2);
    // _rectangle.setOutlineColor(sf::Color::Black);
}

void Display::Box::setPosition(sf::Vector2f position)
{
    _rectangle.setPosition(position);
}

void Display::Box::draw(sf::RenderWindow &window)
{
    window.draw(_rectangle);
}
