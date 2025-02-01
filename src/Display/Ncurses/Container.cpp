/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/Container
** File description:
** Container
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

void Krell::NCursesDisplay::drawBox(int y, int x, int height, int width, const std::string& title)
{
    mvhline(y, x, 0, width);
    mvvline(y, x, 0, height);
    mvvline(y, x + width, 0, height);
    mvhline(y + height, x, 0, width + 1);
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + width, ACS_URCORNER);
    mvaddch(y + height, x, ACS_LLCORNER);
    mvaddch(y + height, x + width, ACS_LRCORNER);

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(y, x + 2, " %s ", title.c_str());
    attroff(COLOR_PAIR(2) | A_BOLD);
}

void Krell::NCursesDisplay::drawHeader(int maxX)
{
    const auto& dateTime = dynamic_cast<const Modules::DateTimeInfo&>(*_modules.at("datetime"));
    const auto& hostInfo = dynamic_cast<const Modules::HostInfo&>(*_modules.at("host"));
    const auto& osInfo = dynamic_cast<const Modules::OsInfo&>(*_modules.at("os"));

    std::string currentTime = dateTime.getCurrentDateTime();
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(1, maxX - currentTime.length() - 2, "%s", currentTime.c_str());
    attroff(COLOR_PAIR(2) | A_BOLD);

    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(1, 2, "%s@%s", hostInfo.getUsername().c_str(), hostInfo.getHostname().c_str());
    attroff(COLOR_PAIR(2) | A_BOLD);
    attron(COLOR_PAIR(3));
    mvprintw(2, 2, "%s (%s)", osInfo.getOsName().c_str(), osInfo.getKernelVersion().c_str());
    attroff(COLOR_PAIR(3));
}