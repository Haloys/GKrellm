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
    _moduleStates['1'] = {"OS Info", true};
    _moduleStates['2'] = {"CPU Info", true};
    _moduleStates['3'] = {"CPU Usage", true};
    _moduleStates['4'] = {"Memory", true};
    _moduleStates['5'] = {"Disk", true};
    _moduleStates['6'] = {"Network", true};
    _moduleStates['7'] = {"System Info", true};
    _moduleStates['8'] = {"Battery", true};
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
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
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
        else if (_moduleStates.find(ch) != _moduleStates.end()) {
            _moduleStates[ch].second = !_moduleStates[ch].second;
            clear();
        }
    }
}

bool Krell::NCursesDisplay::isModuleActive(const std::string& moduleName) const
{
    for (const auto& [key, value] : _moduleStates) {
        if (value.first == moduleName) {
            return value.second;
        }
    }
    return true;
}

bool Krell::NCursesDisplay::isRunning() const
{
    return _isRunning;
}

void Krell::NCursesDisplay::drawModuleStatus(int maxY, int maxX)
{
    (void)maxX;
    std::string controls = "Press 'q' to quit | Modules: ";
    for (const auto& [key, value] : _moduleStates) {
        controls += "'" + std::string(1, key) + "' " + value.first + (value.second ? " [ON]" : " [OFF]") + " | ";
    }
    controls += "Update interval: 100ms";
    attron(A_DIM);
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(maxY - 1, 2, "%s", controls.c_str());
    attroff(COLOR_PAIR(3) | A_BOLD);
    attroff(A_DIM);
}

void Krell::NCursesDisplay::drawModule()
{
    clear();
    int maxY, maxX;
    getmaxyx(_window, maxY, maxX);

    if (isModuleActive("System Info"))
        drawHeader(maxX);
    if (isModuleActive("OS Info"))
        drawOsInfo(maxX);
    if (isModuleActive("CPU Info"))
        drawCpuInfo(maxX);
    if (isModuleActive("CPU Usage"))
        drawCpuUsage(maxX);
    if (isModuleActive("Memory"))
        drawMemoryInfo(maxX);
    if (isModuleActive("Disk"))
        drawDiskInfo(maxX);
    if (isModuleActive("Network"))
        drawNetworkInfo(maxX);
    if (isModuleActive("Battery"))
        drawBatteryInfo(maxX);

    drawHostInfo(maxX);
    drawModuleStatus(maxY, maxX);
}
