/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/IDisplay
** File description:
** modules
*/

#pragma once
#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>

namespace Krell {
    class SFMLDisplay : public IDisplay {
    private:
        sf::RenderWindow _window;
        bool _isRunning;

    public:
        SFMLDisplay();
        ~SFMLDisplay();
        void refresh() override;
        void start() override;
        void stop() override;
    };
}