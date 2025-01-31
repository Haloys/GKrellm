/*
** EPITECH PROJECT, 2025
** Include/SFMLDisplay
** File description:
** SFMLDisplay
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "IDisplay.hpp"
#include "IModule.hpp"

namespace Krell {
    class SFMLDisplay : public IDisplay {
        sf::RenderWindow _window;
        bool _isRunning;
        sf::Font _font;

    public:
        SFMLDisplay();
        ~SFMLDisplay();
        void refresh() override;
        void start() override;
        void stop() override;
        bool isRunning() const override;
        void handleEvents() override;
        void drawModule(const IModule& module) override;
    };
}
