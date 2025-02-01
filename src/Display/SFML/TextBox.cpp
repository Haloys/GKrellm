/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** TextBox
*/

#include "Display/SFML/TextBox.hpp"

Display::TextBox::TextBox(sf::Vector2f size, const std::string &text, const sf::Font &font, bool box) : _box(box)
{
    _rectangle.setSize(size);
    _text.setString(text);
    _text.setFont(font);
    _text.setCharacterSize(20);
    _text.setFillColor(sf::Color::White);
}

void Display::TextBox::setPosition(sf::Vector2f position)
{
    _rectangle.setPosition(position);
    _text.setPosition(position);
}

void Display::TextBox::setText(const std::string &text)
{
    _text.setString(text);
}

void Display::TextBox::draw(sf::RenderWindow &window)
{
    if (_box)
    {
        window.draw(_rectangle);
    }
    window.draw(_text);
}
