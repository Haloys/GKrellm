/*
** EPITECH PROJECT, 2025
** Include/Display/SFML/ProgressBar
** File description:
** ProgressBar
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Display/SFML/Box.hpp"

namespace Display
{
    class ProgressBar
    {
    public:
        ProgressBar(sf::Vector2f size);
        void setPosition(sf::Vector2f position);
        void setProgress(double percentage);
        void draw(sf::RenderWindow &window);

    private:
        Box _box;
        sf::RectangleShape _progress;
        sf::RectangleShape _background;
    };
}
