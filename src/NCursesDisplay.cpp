/*
** EPITECH PROJECT, 2025
** src/NcursesDisplay
** File description:
** NcursesDisplay
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

#include <thread>

Krell::NCursesDisplay::NCursesDisplay() : IDisplay(), _isRunning(false)
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
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    keypad(_window, TRUE);
    nodelay(_window, TRUE);
    timeout(0);
    _isRunning = true;
    curs_set(0);
}

void Krell::NCursesDisplay::refresh()
{
    refresh_all();
    ::refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Krell::NCursesDisplay::stop()
{
    endwin();
    _isRunning = false;
}

void Krell::NCursesDisplay::handleEvents()
{
    int ch = getch();
    if (ch != ERR) {
        if (ch == 'q' || ch == 'Q') {
            _isRunning = false;
        }
    }
}

bool Krell::NCursesDisplay::isRunning() const
{
    return _isRunning;
}


void Krell::NCursesDisplay::drawModule()
{
    clear();
    int maxY, maxX;
    getmaxyx(_window, maxY, maxX);

    drawCpuInfo(maxX);
    drawCpuUsage(maxX);
    drawMemoryInfo(maxX);

    attron(A_DIM);
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(maxY - 1, 2, "Press 'q' to quit | Update interval: 100ms");
    attroff(COLOR_PAIR(3) | A_BOLD);
    attroff(A_DIM);
}