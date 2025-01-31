/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/src/Modules/CpuUsage
** File description:
** cpu
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "Modules/CpuUsage.hpp"

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
    // Debug:
    std::cerr << "Raw line: " << line << std::endl;
    std::istringstream ss(line);
    std::string cpu;
    ss >> cpu;
    ss >> _user >> _nice >> _system >> _idle >> _iowait >> _irq >> _softirq;

    _total = _user + _nice + _system + _idle + _iowait + _irq + _softirq;
    _used = _total - _idle;
    _free = _idle;

    auto now = time(nullptr);
    if (_lastRefresh != 0) {
        usedPercent = 100 * (used - _used) / (_total - total);
        freePercent = 100 * (free - _free) / (_total - total);


        total = _total;
        used = _used;
        free = _free;
    } else {
        total = 0;
        used = 0;
        free = 0;
    }
}

double Krell::Modules::CpuUsage::getValue(const std::string& key) const
{
    if (key == "total")
        return static_cast<double>(total);
    if (key == "used")
        return static_cast<double>(used);
    if (key == "free")
        return static_cast<double>(free);
    if (key == "usedPercent")
        return static_cast<double>(usedPercent());
    if (key == "freePercent")
        return static_cast<double>(freePercent());
    return 0.0;
}
