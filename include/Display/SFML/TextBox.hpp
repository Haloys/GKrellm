/*
** EPITECH PROJECT, 2025
** Include/Display/SFML
** File description:
** TextBox
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Display {
    class TextBox {
        public:
            TextBox(sf::Vector2f size, const std::string &text, const sf::Font &font, bool box = false);
            ~TextBox() = default;

            void setPosition(sf::Vector2f position);
            void setText(const std::string &text);

            void draw(sf::RenderWindow &window);

        private:
            sf::RectangleShape _rectangle;
            sf::Text _text;
            bool _box;
    };
}
