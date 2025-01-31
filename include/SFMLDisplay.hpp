/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/IDisplay
** File description:
** modules
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IDisplay.hpp"

namespace Krell {
    class SFMLDisplay : public IDisplay {
        sf::RenderWindow _window;
        bool _isRunning;

    public:
        SFMLDisplay();
        ~SFMLDisplay();
        void refresh() override;
        void start() override;
        void stop() override;
        bool isRunning() const override;
        void handleEvents() override;
    };
}