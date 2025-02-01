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
        private:
            WINDOW* _window;
            bool _isRunning;

            void drawBox(int y, int x, int height, int width, const std::string& title);
            void drawProgressBar(int y, int x, double percentage, int width);

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
