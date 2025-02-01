/*
** EPITECH PROJECT, 2025
** src/Modules/MemoryInfo
** File description:
** MemoryInfo
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "Modules/MemoryInfo.hpp"

Krell::Modules::MemoryInfo::MemoryInfo()
{
    refresh();
}

Krell::Modules::MemoryInfo::~MemoryInfo()
{
}

void Krell::Modules::MemoryInfo::refresh()
{
    std::ifstream file("/proc/meminfo");
    std::string line;
    std::string key;
    size_t value;

    if (!file.is_open()) {
        return;
    }
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> key >> value;
        key.erase(key.find_last_not_of(" \t") + 1);
        _memoryInfo[key] = value;
    }
}

double Krell::Modules::MemoryInfo::getValue(ModuleKey key) const
{
    try {
        if (key == TOTAL)
            return static_cast<double>(Total());
        if (key == USED)
            return static_cast<double>(Used());
        if (key == FREE)
            return static_cast<double>(Free());
        if (key == USEDPERCENT)
            return static_cast<double>(usePercentage());
        if (key == FREEPERCENT)
            return static_cast<double>(freePercentage());
        if (key == AVAILABLE)
            return static_cast<double>(Available());
        if (key == AVAILABLEPERCENT)
            return static_cast<double>(availablePercentage());
        if (key == SWAP_TOTAL)
            return static_cast<double>(SwapTotal());
        if (key == SWAP_USED)
            return static_cast<double>(SwapUsed());
        if (key == SWAP_PERCENT)
            return static_cast<double>(swapUsePercentage());
        return 0.0;
    } catch (const std::exception&) {
        return 0.0;
    }
}

void Krell::Modules::MemoryInfo::drawModule(SFMLDisplay &disp)
{

}
