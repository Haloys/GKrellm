/*
** EPITECH PROJECT, 2025
** Include/Display/SFML/Container
** File description:
** Container
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace Display
{
    class Container
    {
    public:
        Container(const sf::Vector2f &position, const sf::Vector2f &size)
            : _position(position), _size(size) {}

        void setPosition(const sf::Vector2f &position);

        void setSize(const sf::Vector2f &size);

        const sf::Vector2f &getPosition() const;

        const sf::Vector2f &getSize() const;

    private:
        sf::Vector2f _position;
        sf::Vector2f _size;
    };
}
