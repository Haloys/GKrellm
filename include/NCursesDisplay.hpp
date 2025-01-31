/*
** EPITECH PROJECT, 2025
** Include/NcursesDisplay
** File description:
** NcursesDisplay
*/

#pragma once

#include <ncurses.h>

#include "IDisplay.hpp"
#include "IModule.hpp"

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
        void drawModule(const IModule& module) override;
    };
}
