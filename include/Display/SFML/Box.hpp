/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** Box
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Box {
    class Box {
        public:
            Box(sf::Vector2f size);
            ~Box() = default;

            void setPosition(sf::Vector2f position);

            void draw(sf::RenderWindow &window);

        private:
            sf::RectangleShape _rectangle;
    };
}
