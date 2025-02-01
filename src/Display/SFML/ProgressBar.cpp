/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** ProgressBar
*/

#include "SFMLDisplay.hpp"
#include "Display/SFML/ProgressBar.hpp"

namespace Display
{
    ProgressBar::ProgressBar(sf::Vector2f size) : _box(size)
    {
        _progress.setSize(sf::Vector2f(size.x - 20, size.y - 20));
        _progress.setFillColor(BAR_COLOR_GREEN);
    }

    void ProgressBar::setPosition(sf::Vector2f position)
    {
        _box.setPosition(position);
        _progress.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
    }

    void ProgressBar::setProgress(double percentage)
    {
        sf::Vector2f size = _box.getRectangle().getSize();
        size.x = (size.x - 20) * (percentage / 100.0f);
        size.y -= 20;
        _progress.setSize(size);
    }

    void ProgressBar::draw(sf::RenderWindow &window)
    {
        _box.draw(window);
        window.draw(_progress);
    }
}
