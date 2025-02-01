/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/ProgressBar
** File description:
** ProgressBar
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

void Krell::NCursesDisplay::drawProgressBar(int y, int x, double percentage, int width)
{
    mvprintw(y, x, "[");
    int totalUsedWidth = static_cast<int>((percentage / 100.0) * (width - 2));
    int greenWidth = std::min(totalUsedWidth, (width - 2) / 2);
    int orangeWidth = 0;
    int redWidth = 0;

    if (percentage > 50) {
        orangeWidth = std::min(totalUsedWidth - greenWidth, static_cast<int>((width - 2) * 0.3));
    }
    if (percentage > 80) {
        redWidth = totalUsedWidth - greenWidth - orangeWidth;
    }

    attron(COLOR_PAIR(1));
    for (int i = 0; i < greenWidth; i++)
        printw("|");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4));
    for (int i = 0; i < orangeWidth; i++)
        printw("|");
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(5));
    for (int i = 0; i < redWidth; i++)
        printw("|");
    attroff(COLOR_PAIR(5));

    for (int i = totalUsedWidth; i < width - 2; i++)
        printw(" ");
    printw("] %5.1f%%", percentage);
}
