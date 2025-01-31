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
    total = _total;
    used = _used;
    free = _free;

    // Debug:
    std::cerr   << "Debug CPU Values:" << std::endl
                << "  Raw values:" << std::endl
                << "    user: " << _user << std::endl
                << "    nice: " << _nice << std::endl
                << "    system: " << _system << std::endl
                << "    idle: " << _idle << std::endl
                << "    iowait: " << _iowait << std::endl
                << "    irq: " << _irq << std::endl
                << "    softirq: " << _softirq << std::endl
                << "  Calculated values:" << std::endl
                << "    Total: " << _total << std::endl
                << "    Used: " << _used << std::endl
                << "    Free: " << _free << std::endl
                << "    CPU Usage: " << (static_cast<double>(_used) * 100.0 / static_cast<double>(_total)) << "%"
                << std::endl << "-------------------------------" << std::endl;
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