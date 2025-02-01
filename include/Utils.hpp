/*
** EPITECH PROJECT, 2025
** Include/SFMLDisplay
** File description:
** SFMLDisplay
*/

#pragma once

#include <SFML/System/Vector2.hpp>

sf::Vector2f vecCalc(const sf::Vector2f& vec, float x, float y) {
    return sf::Vector2f(vec.x + x, vec.y + y);
}
