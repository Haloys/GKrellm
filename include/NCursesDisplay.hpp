/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/IDisplay
** File description:
** modules
*/

#pragma once
#include "IDisplay.hpp"
#include <ncurses.h>

namespace Krell {
    class NCursesDisplay : public IDisplay {
    private:
        WINDOW* _window;
        bool _isRunning;

    public:
        NCursesDisplay();
        ~NCursesDisplay();
        void refresh() override;
        void start() override;
        void stop() override;
    };
}
