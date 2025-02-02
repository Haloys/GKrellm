/*
** EPITECH PROJECT, 2025
** Include/NcursesDisplay
** File description:
** NcursesDisplay
*/

#pragma once

#include <ncurses.h>
#include <map>

#include "IDisplay.hpp"
#include "IModule.hpp"

namespace Krell {
    class NCursesDisplay : public IDisplay {
        private:
            WINDOW* _window;
            bool _isRunning;
            std::map<char, std::pair<std::string, bool>> _moduleStates;

            void drawBox(int y, int x, int height, int width, const std::string& title);
            void drawProgressBar(int y, int x, double percentage, int width);

            void drawHeader(int maxX);
            void drawDateTime(int maxX);
            void drawCpuInfo(int maxX);
            void drawCpuUsage(int maxX);
            void drawMemoryInfo(int maxX);
            void drawHostInfo(int maxX);
            void drawOsInfo(int maxX);
            void drawNetworkInfo(int maxX);
            void drawDiskInfo(int maxX);
            void drawModuleStatus(int maxY, int maxX);
            void drawBatteryInfo(int maxX);

        public:
            NCursesDisplay();
            ~NCursesDisplay();
            void refresh() override;
            void start() override;
            void stop() override;
            bool isRunning() const override;
            void handleEvents() override;
            void drawModule() override;
            bool isModuleActive(const std::string& moduleName) const;
    };
}