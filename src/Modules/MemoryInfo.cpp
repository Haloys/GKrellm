/*
** EPITECH PROJECT, 2025
** src/Modules/MemoryInfo
** File description:
** memory info module implementation
*/

#include "Modules/MemoryInfo.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

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
