/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** Chart
*/

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Display/SFML/Box.hpp"

namespace Display
{
    class ClockDisplay
    {
    public:
        ClockDisplay(const sf::Vector2f &size, const sf::Vector2f &position);

        void update();
        void draw(sf::RenderWindow &window);

    private:
        Display::Box _box;
        sf::Text _text;
        sf::Font _font;
        sf::Vector2f _position;
    };
}
