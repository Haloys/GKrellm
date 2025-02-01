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

Display::ProgressBar::ProgressBar(sf::Vector2f size, const sf::Font &font) : _box(size)
{
    _background.setSize(sf::Vector2f(size.x - 20, size.y - 20));
    _background.setFillColor(BG_COLOR_CLICK);
    _progress.setSize(sf::Vector2f(size.x - 20, size.y - 20));
    _progress.setFillColor(BAR_COLOR_GREEN);
    _txt.setFont(font);
    _txt.setFillColor(TEXT_COLOR_WHITE);
    _txt.setString("0%");
}

void Display::ProgressBar::setPosition(sf::Vector2f position)
{
    sf::Vector2f size = _box.getRectangle().getSize();

    _box.setPosition(position);
    _background.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
    _progress.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
    _txt.setPosition(sf::Vector2f(position.x + size.x / 2 - 18, position.y + 15));
    _txt.setCharacterSize(18);
}

void Display::ProgressBar::setProgress(double percentage, bool difColor)
{
    sf::Vector2f size = _box.getRectangle().getSize();
    size.x = (size.x - 20) * (percentage / 100.0f);
    size.y -= 20;
    _progress.setSize(size);
    _progress.setFillColor(BAR_COLOR_GREEN);
    _txt.setString(std::to_string(int(percentage)) + "%");
    _txt.setFillColor(TEXT_COLOR_WHITE);

    if (difColor == false || percentage <= 25)
    {
        return;
    }
    if (percentage <= 50)
    {
        _progress.setFillColor(BAR_COLOR_YELLOW);
        _txt.setFillColor(TEXT_COLOR_BLACK);
    }
    else if (percentage <= 75)
    {
        _progress.setFillColor(BAR_COLOR_ORANGE);
    }
    else
    {
        _progress.setFillColor(BAR_COLOR_RED);
    }
}

void Display::ProgressBar::draw(sf::RenderWindow &window)
{
    _box.draw(window);
    window.draw(_background);
    window.draw(_progress);
    window.draw(_txt);
}
