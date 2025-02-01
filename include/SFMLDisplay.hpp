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

#define FONT_PATH "assets/font/Arial.ttf"

#define BG_COLOR sf::Color(32, 32, 32)
#define BOX_COLOR sf::Color(50, 50, 50)
#define BG_COLOR_CLICK sf::Color(27, 27, 27)
#define BAR_COLOR_GREEN sf::Color(100, 250, 50)
#define BAR_COLOR_YELLOW sf::Color(250, 250, 50)
#define BAR_COLOR_ORANGE sf::Color(250, 150, 50)
#define BAR_COLOR_RED sf::Color(250, 100, 50)
#define BAR_COLOR_BLUE sf::Color(50, 100, 250)
#define BG_COLOR_TEST sf::Color(43, 42, 42)
#define TEXT_COLOR_WHITE sf::Color::White
#define TEXT_COLOR_BLACK sf::Color::Black

namespace Krell {
    class SFMLDisplay : public IDisplay {
        sf::RenderWindow _window;
        bool _isRunning;
        sf::Font _font;
        int _refreshDelay;
        sf::Clock _delayClock;

    public:
        SFMLDisplay();
        ~SFMLDisplay();
        void refresh() override;
        void start() override;
        void stop() override;
        bool isRunning() const override;
        void handleEvents() override;
        void drawModule(const IModule& module) { (void)module; }
        sf::Font &getFont() { return _font; }
        int getRefreshDelay() { return _refreshDelay; }
        sf::Clock &getDelayClock() { return _delayClock; }
        sf::RenderWindow &getWindow() { return _window; }
    };
}
