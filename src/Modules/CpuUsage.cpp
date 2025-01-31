/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/src/Modules/CpuUsage
** File description:
** cpu
*/

#include "Modules/CpuUsage.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

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
        return;
    }
    std::istringstream ss(line);

    ss.ignore(5);
    ss >> _user >> _nice >> _system >> _idle >> _iowait >> _irq >> _softirq;

    _total = _user + _nice + _system + _idle + _iowait + _irq + _softirq;
    _used = _total - _idle;
    _free = _idle;

    total = _total;
    used = _used;
    free = _free;
}
