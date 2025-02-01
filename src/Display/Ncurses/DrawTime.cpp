/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawTime
** File description:
** DrawTime
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

#include <iostream>
#include <cstring>

void Krell::NCursesDisplay::drawDateTime(int maxX)
{
    const auto& dateTime = dynamic_cast<const Modules::DateTimeInfo&>(*_modules.at("datetime"));
    std::string currentTime = dateTime.getCurrentDateTime();
    int dateLength = dateTime.getDateLength();
    int boxWidth = dateLength + 4;
    int startX = (maxX - boxWidth) / 2;

    mvhline(1, startX + 1, ACS_HLINE, boxWidth - 2);
    mvhline(3, startX + 1, ACS_HLINE, boxWidth - 2);
    mvvline(2, startX, ACS_VLINE, 1);
    mvvline(2, startX + boxWidth - 1, ACS_VLINE, 1);
    mvaddch(1, startX, ACS_ULCORNER);
    mvaddch(1, startX + boxWidth - 1, ACS_URCORNER);
    mvaddch(3, startX, ACS_LLCORNER);
    mvaddch(3, startX + boxWidth - 1, ACS_LRCORNER);
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(2, startX + 2, "%s", currentTime.c_str());
    attroff(COLOR_PAIR(2) | A_BOLD);
}
