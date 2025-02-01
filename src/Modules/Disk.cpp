/*
** EPITECH PROJECT, 2025
** /home/vj/coding/t2r3/src/Modules/Disk
** File description:
** disk info mostly just disk usage
*/


#include <fstream>
#include <sstream>

#include "Modules/Disk.hpp"

Krell::Modules::Disk::Disk() : _used(0), _free(0), _total(0), _usedPercent(0), _freePercent(0)
{
    refresh();
}

Krell::Modules::Disk::~Disk() {}

void Krell::Modules::Disk::refresh()
{
    std::ifstream file("/proc/mounts");
    std::string line;
    std::string device;
    std::string mountPoint;
    std::string type;
    std::string options;
    std::string dump;
    std::string pass;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        ss >> device >> mountPoint >> type >> options >> dump >> pass;
        if (mountPoint == "/") {
            break;
        }
    }
    file.close();

    file.open("/proc/self/mountstats");
    if (!file.is_open()) {
        return;
    }
    while (std::getline(file, line)) {
        if (line.find(device) != std::string::npos) {
            break;
        }
    }
    while (std::getline(file, line)) {
        if (line.find("total=") != std::string::npos) {
            std::istringstream ss(line);
            std::string tmp;
            ss >> tmp >> _total;
        }
        if (line.find("free=") != std::string::npos) {
            std::istringstream ss(line);
            std::string tmp;
            ss >> tmp >> _free;
        }
        if (line.find("used=") != std::string::npos) {
            std::istringstream ss(line);
            std::string tmp;
            ss >> tmp >> _used;
        }
    }
    file.close();

    if (_total == 0) {
        return;
    }
    _usedPercent = (_used * 100) / _total;
    _freePercent = (_free * 100) / _total;
}

double Krell::Modules::Disk::getValue(ModuleKey key) const
{
    if (key == USED)
        return static_cast<double>(_used);
    if (key == FREE)
        return static_cast<double>(_free);
    if (key == TOTAL)
        return static_cast<double>(_total);
    if (key == USEDPERCENT)
        return static_cast<double>(_usedPercent);
    if (key == FREEPERCENT)
        return static_cast<double>(_freePercent);
    return 0.0;
}
