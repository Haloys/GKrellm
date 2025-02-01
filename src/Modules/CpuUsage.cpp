/*
** EPITECH PROJECT, 2025
** src/Modules/CpuUsage
** File description:
** CpuUsage
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "Modules/CpuUsage.hpp"
#include "IModule.hpp"

Krell::Modules::CpuUsage::CpuUsage()
{
    refresh();
}

Krell::Modules::CpuUsage::~CpuUsage()
{
}

void Krell::Modules::CpuUsage::refresh()
{
    std::ifstream file("/proc/stat");
    std::string line;

    if (!std::getline(file, line)) {
        std::cerr << "Failed to read /proc/stat" << std::endl;
        return;
    }
    std::istringstream ss(line);
    std::string cpu;
    ss >> cpu;
    ss >> _user >> _nice >> _system >> _idle >> _iowait >> _irq >> _softirq;

    _total = _user + _nice + _system + _idle + _iowait + _irq + _softirq;
    _used = _total - _idle;
    _free = _idle;

    if (total - _total == 0) {
        return;
    }
    usedPercent = 100 * (_used - used) / (_total - total);
    freePercent = 100 * (_free - free) / (_total - total);

    total = _total;
    used = _used;
    free = _free;
}

double Krell::Modules::CpuUsage::getValue(ModuleKey key) const
{
    if (key == TOTAL)
        return static_cast<double>(total);
    if (key == USED)
        return static_cast<double>(used);
    if (key == FREE)
        return static_cast<double>(free);
    if (key == USEDPERCENT)
        return static_cast<double>(usedPercent);
    if (key == FREEPERCENT)
        return static_cast<double>(freePercent);
    return 0.0;
}
