/*
** EPITECH PROJECT, 2025
** src/Modules/Battery
** File description:
** Battery
*/

#include <fstream>

#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "Modules/Battery.hpp"
#include "IModule.hpp"
#include "Utils.hpp"

Krell::Modules::Battery::Battery() : IModule(sf::Vector2f(500, 700), sf::Vector2f(400, 100), "Battery"), _batteryPercent(0), _batteryTime(0), _charging(false)
{

}

Krell::Modules::Battery::~Battery()
{

}

void Krell::Modules::Battery::refresh()
{
    static std::string lastFoundBattery;

    if (lastFoundBattery.empty()) {
        const std::vector<std::string> batteryNames = {
            "BAT0", "BAT1", "BAT2",
            "CMB0", "CMB1",
            "BATT", "BATC",
            "macsmc-battery"
        };

        for (const auto& name : batteryNames) {
            std::string path = "/sys/class/power_supply/" + name + "/capacity";
            std::ifstream test(path);
            if (test.is_open()) {
                lastFoundBattery = name;
                test.close();
                break;
            }
        }

        if (lastFoundBattery.empty()) {
            _batteryPercent = 0;
            _charging = false;
            return;
        }
    }

    std::ifstream file("/sys/class/power_supply/" + lastFoundBattery + "/capacity");
    if (file.is_open()) {
        file >> _batteryPercent;
        file.close();
    }

    file.open("/sys/class/power_supply/" + lastFoundBattery + "/status");
    if (file.is_open()) {
        std::string status;
        file >> status;
        if (status == "Charging" || status == "Not discharging") {
            _charging = true;
        } else if (status == "Discharging" || status == "Not charging") {
            _charging = false;
        }
        file.close();
    }
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
    Display::Container container(pos, size);
    Display::ProgressBar progressBar(sf::Vector2f(360, 50), disp.getFont());

    container.draw(disp.getWindow());

    Display::TextBox batteryTextBox(sf::Vector2f(20, 20), "Battery Status", disp.getFont());
    batteryTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    batteryTextBox.draw(disp.getWindow());

    std::string batteryInfo = "Battery: " + std::to_string(static_cast<int>(getValue(IModule::TOTAL))) + "%\n";

    Display::TextBox modelTextBox(sf::Vector2f(20, 20), batteryInfo, disp.getFont());
    modelTextBox.setPosition(vecCalc(container.getPosition(), 20, 50));
    modelTextBox.draw(disp.getWindow());
}
