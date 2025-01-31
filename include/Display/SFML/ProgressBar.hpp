/*
** EPITECH PROJECT, 2025
** Src/main
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
        void setProgress(float percentage);
        void draw(sf::RenderWindow &window);

    private:
        Box _box;
        sf::RectangleShape _progress;
    };
}
