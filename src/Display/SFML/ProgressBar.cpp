/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** ProgressBar
*/

#include "SFMLDisplay.hpp"
#include "Display/SFML/ProgressBar.hpp"

#define BAR_COLOR_GREEN sf::Color(100, 250, 50)
#define BAR_COLOR_YELLOW sf::Color(250, 250, 50)
#define BAR_COLOR_ORANGE sf::Color(250, 150, 50)
#define BAR_COLOR_RED sf::Color(250, 100, 50)

namespace Display
{
    ProgressBar::ProgressBar(sf::Vector2f size) : _box(size)
    {
        _background.setSize(sf::Vector2f(size.x - 20, size.y - 20));
        _background.setFillColor(BG_COLOR_CLICK);
        _progress.setSize(sf::Vector2f(size.x - 20, size.y - 20));
        _progress.setFillColor(BAR_COLOR_GREEN);
    }

    void ProgressBar::setPosition(sf::Vector2f position)
    {
        _box.setPosition(position);
        _background.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
        _progress.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
    }

    void ProgressBar::setProgress(double percentage, bool difColor)
    {
        sf::Vector2f size = _box.getRectangle().getSize();
        size.x = (size.x - 20) * (percentage / 100.0f);
        size.y -= 20;
        _progress.setSize(size);
        _progress.setFillColor(BAR_COLOR_GREEN);

        if (difColor == false || percentage <= 25) {
            return;
        }
        if (percentage <= 50) {
            _progress.setFillColor(BAR_COLOR_YELLOW);
        } else if (percentage <= 75) {
            _progress.setFillColor(BAR_COLOR_ORANGE);
        } else {
            _progress.setFillColor(BAR_COLOR_RED);
        }
    }

    void ProgressBar::draw(sf::RenderWindow &window)
    {
        _box.draw(window);
        window.draw(_background);
        window.draw(_progress);
    }
}
