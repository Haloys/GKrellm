/*
** EPITECH PROJECT, 2025
** /home/vj/coding/t2r3/src/Modules/Battery
** File description:
** oewub
*/

#include <fstream>

#include "Modules/Battery.hpp"

Krell::Modules::Battery::Battery() :
    IModule(sf::Vector2f(0, 0)),
    _batteryPercent(0), _batteryTime(0), _charging(false)
{
}

Krell::Modules::Battery::~Battery() {}

void Krell::Modules::Battery::refresh() {
    std::ifstream file("/sys/class/power_supply/BAT0/capacity");
    if (!file.is_open()) {
        return;
    }
    file >> _batteryPercent;
    file.close();

    file.open("/sys/class/power_supply/BAT0/status");
    if (!file.is_open()) {
        return;
    }
    std::string status;
    file >> status;
    if (status == "Charging") {
        _charging = true;
    } else {
        _charging = false;
    }
    file.close();

    //might not exist
    file.open("/sys/class/power_supply/BAT0/time_to_empty_now");
    if (!file.is_open()) {
        return;
    }
    file >> _batteryTime;
    file.close();
}
