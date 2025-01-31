/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/IDisplay
** File description:
** modules
*/

#pragma once

#include <ncurses.h>

#include "IDisplay.hpp"

namespace Krell {
    class NCursesDisplay : public IDisplay {
        WINDOW* _window;
        bool _isRunning;

    public:
        NCursesDisplay();
        ~NCursesDisplay();
        void refresh() override;
        void start() override;
        void stop() override;
        bool isRunning() const override;
        void handleEvents() override;
    };
}
