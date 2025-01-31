/*
** EPITECH PROJECT, 2025
** Src/NcursesDisplay
** File description:
** NcursesDisplay
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

Krell::NCursesDisplay::NCursesDisplay() : _isRunning(false), IDisplay()
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

void Krell::NCursesDisplay::drawModule(const IModule& module)
{
    static int yPos = 1;

    mvprintw(yPos, 1, "CPU Usage");
    float usagePercent = static_cast<float>(module.getValue("used")) /
                        static_cast<float>(module.getValue("total")) * 100.0f;
    mvprintw(yPos + 1, 1, "[");
    int barWidth = 50;
    int usedWidth = static_cast<int>((usagePercent / 100.0f) * barWidth);
    attron(COLOR_PAIR(1));
    for (int i = 0; i < usedWidth; i++)
        mvprintw(yPos + 1, 2 + i, "|");
    attroff(COLOR_PAIR(1));
    for (int i = usedWidth; i < barWidth; i++)
        mvprintw(yPos + 1, 2 + i, " ");
    mvprintw(yPos + 1, 2 + barWidth, "] %d%%", static_cast<int>(usagePercent));
    yPos += 3;
}