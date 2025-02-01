/*
** EPITECH PROJECT, 2025
** src/Modules/DateTimeInfo
** File description:
** DateTimeInfo
*/

#include <ctime>
#include <iomanip>

#include "Modules/DateTimeInfo.hpp"

Krell::Modules::DateTimeInfo::DateTimeInfo()
{
    refresh();
}

void Krell::Modules::DateTimeInfo::refresh()
{
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    _currentDateTime = buffer;
}

double Krell::Modules::DateTimeInfo::getValue(ModuleKey key) const
{
    (void)key;
    return 0.0;
}
