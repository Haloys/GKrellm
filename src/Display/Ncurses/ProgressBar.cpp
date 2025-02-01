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
    int usedWidth = static_cast<int>((percentage / 100.0) * (width - 2));
    attron(COLOR_PAIR(1));
    for (int i = 0; i < usedWidth; i++)
        printw("|");
    attroff(COLOR_PAIR(1));
    for (int i = usedWidth; i < width - 2; i++)
        printw(" ");
    printw("] %5.1f%%", percentage);
}
