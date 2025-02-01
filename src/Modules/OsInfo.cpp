/*
** EPITECH PROJECT, 2025
** src/Modules/OsInfo
** File description:
** OsInfo
*/

#include <fstream>
#include <sstream>
#include "Modules/OsInfo.hpp"

Krell::Modules::OsInfo::OsInfo() : IModule(sf::Vector2f(0, 0))
{
    refresh();
}

void Krell::Modules::OsInfo::refreshOsInfo()
{
    struct utsname systemInfo;
    if (uname(&systemInfo) == -1) {
        _kernelVersion = "unknown";
        _machine = "unknown";
        return;
    }
    _kernelVersion = systemInfo.release;
    _machine = systemInfo.machine;

    std::ifstream osRelease("/etc/os-release");
    std::string line;
    if (osRelease.is_open()) {
        while (std::getline(osRelease, line)) {
            if (line.substr(0, 5) == "NAME=") {
                _osName = line.substr(5);
                if (_osName.front() == '"') {
                    _osName = _osName.substr(1, _osName.length() - 2);
                }
                break;
            }
        }
    } else {
        _osName = "Linux";
    }
}

void Krell::Modules::OsInfo::refresh()
{
    refreshOsInfo();
}

double Krell::Modules::OsInfo::getValue(ModuleKey key) const
{
    (void)key;
    return 0.0;
}
