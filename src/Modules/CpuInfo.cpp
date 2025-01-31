/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/src/Modules/CpuInfo
** File description:
** cpu
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "Modules/CpuInfo.hpp"

Krell::Modules::CpuInfo::CpuInfo()
{
    refresh();
}

Krell::Modules::CpuInfo::~CpuInfo()
{
}

void Krell::Modules::CpuInfo::refresh()
{
    std::ifstream file("/proc/cpuinfo");

    if (!file.is_open()) {
        return;
    }
    std::string line;
    std::string key;
    std::string value;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::getline(ss, key, ':');
        std::getline(ss, value);
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        _cpuInfo[key] = value;
    }
}

double Krell::Modules::CpuInfo::getValue(const std::string& key) const
{
    if (key == "cores")
        return static_cast<double>(CpuCores());
    if (key == "threads")
        return static_cast<double>(CpuThreads());
    if (key == "mhz")
        return static_cast<double>(CpuMhz());
    return 0.0;
}