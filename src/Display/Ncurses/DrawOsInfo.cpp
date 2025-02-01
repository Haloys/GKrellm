/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawOsInfo
** File description:
** DrawOsInfo
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

void Krell::NCursesDisplay::drawOsInfo(int maxX)
{
    const auto& osInfo = dynamic_cast<const Modules::OsInfo&>(*_modules.at("os"));

    drawBox(33, 1, 3, maxX - 3, "Operating System Information");
    mvprintw(34, 3, "OS: %s", osInfo.getOsName().c_str());
    mvprintw(35, 3, "Kernel: %s (%s)", osInfo.getKernelVersion().c_str(), osInfo.getMachine().c_str());
}