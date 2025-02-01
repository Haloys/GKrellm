/*
** EPITECH PROJECT, 2025
** Include/Display/SFML/Chart
** File description:
** Chart
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Display
{
    class Chart
    {
    public:
        Chart(sf::Vector2f size);
        void setPosition(sf::Vector2f position);
        void setData(const std::vector<float>& data, bool difColor);
        void draw(sf::RenderWindow &window);

    private:
        sf::RectangleShape _background;
        std::vector<sf::RectangleShape> _bars;
        sf::Vector2f _size;
    };
}
