/*
** EPITECH PROJECT, 2025
** Src/NcursesDisplay
** File description:
** NcursesDisplay
*/

#include "NCursesDisplay.hpp"

Krell::NCursesDisplay::NCursesDisplay() : _isRunning(false)
{

}

Krell::NCursesDisplay::~NCursesDisplay()
{
    if (_isRunning) {
        stop();
    }
}

void Krell::NCursesDisplay::start()
{
    _window = initscr();
    noecho();
    cbreak();
    keypad(_window, TRUE);
    _isRunning = true;
}

void Krell::NCursesDisplay::refresh()
{
    ::refresh();
}

void Krell::NCursesDisplay::stop()
{
    endwin();
    _isRunning = false;
}

void Krell::NCursesDisplay::handleEvents()
{
    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
        _isRunning = false;
    }
}

bool Krell::NCursesDisplay::isRunning() const
{
    return _isRunning;
}
