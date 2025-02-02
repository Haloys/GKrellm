/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawBattery
** File description:
** DrawBattery
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

void Krell::NCursesDisplay::drawBatteryInfo(int maxX)
{
    const auto& batteryInfo = dynamic_cast<const Modules::Battery&>(*_modules.at("battery"));
    bool isCharging = batteryInfo.isCharging();
    int percent = batteryInfo.getBatteryPercent();
    int color = COLOR_PAIR(1);
    if (percent <= 20) {
        color = COLOR_PAIR(5);
    } else if (percent <= 40) {
        color = COLOR_PAIR(4);
    }

    std::string batteryStatus = "Battery: " + std::to_string(percent) + "%" + (isCharging ? " [Charging]" : " [Not Charging]");
    int xPos = maxX - batteryStatus.length() - 2;

    attron(color | A_BOLD);
    mvprintw(3, xPos, "%s", batteryStatus.c_str());
    attroff(color | A_BOLD);
}