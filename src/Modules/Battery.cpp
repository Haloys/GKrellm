/*
** EPITECH PROJECT, 2025
** /home/vj/coding/t2r3/src/Modules/Battery
** File description:
** oewub
*/

#include <fstream>

#include "Modules/Battery.hpp"
#include "IModule.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "Utils.hpp"

Krell::Modules::Battery::Battery() :
    IModule(sf::Vector2f(100, 100)),
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

double Krell::Modules::Battery::getValue(ModuleKey key) const
{
    if (key == ModuleKey::UP)
        return isCharging();
    if (key == ModuleKey::TOTAL)
        return getBatteryPercent();
    if (key == ModuleKey::USED)
        return getBatteryTime();
    return 0.0;
}

void Krell::Modules::Battery::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(50, 370), size);
    Display::ProgressBar progressBar(sf::Vector2f(360, 50), disp.getFont());

    container.draw(disp.getWindow());

    Display::TextBox cpuInfoTextBox(sf::Vector2f(20, 20), "Battery", disp.getFont());
    cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 200, 200));
    cpuInfoTextBox.draw(disp.getWindow());

    std::string batteryInfo = "Battery: " + std::to_string(getValue(IModule::TOTAL)) + "%\n";


    Display::TextBox modelTextBox(sf::Vector2f(20, 20), batteryInfo, disp.getFont());
    modelTextBox.setPosition(vecCalc(container.getPosition(), 200, 500));
    modelTextBox.draw(disp.getWindow());
}
