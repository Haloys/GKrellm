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
