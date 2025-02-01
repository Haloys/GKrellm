/*
** EPITECH PROJECT, 2025
** Include/Display/SFML/Container
** File description:
** Container
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "SFMLDisplay.hpp"

namespace Display {
    class Container {
        public:
            Container(const sf::Vector2f &position, const sf::Vector2f &size) : _position(position), _size(size)
            {
                _rectangle.setPosition(position);
                _rectangle.setSize(size);
                _rectangle.setFillColor(BG_COLOR_TEST);
            }

            void setPosition(const sf::Vector2f &position);

            void setSize(const sf::Vector2f &size);

            const sf::Vector2f &getPosition() const;

            const sf::Vector2f &getSize() const;

            void draw(sf::RenderWindow &window);

        private:
            sf::Vector2f _position;
            sf::Vector2f _size;
            sf::RectangleShape _rectangle;
    };
}
