/*
** EPITECH PROJECT, 2025
** Include/Display/SFML
** File description:
** Box
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Display {
    class Box {
    public:
        Box(sf::Vector2f size);
        ~Box() = default;

        void setPosition(sf::Vector2f position);

        void draw(sf::RenderWindow &window);

        sf::RectangleShape getRectangle() { return _rectangle; }

    private:
        sf::RectangleShape _rectangle;
    };
}
