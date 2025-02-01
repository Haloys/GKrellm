/*
** EPITECH PROJECT, 2025
** src/Modules/OsInfo
** File description:
** OsInfo
*/

#include <fstream>
#include <sstream>
#include "Modules/OsInfo.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Utils.hpp"

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

void Krell::Modules::OsInfo::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(420, 0), size);

    container.draw(disp.getWindow());

    Display::TextBox cpuInfoTextBox(sf::Vector2f(20, 20), "Host", disp.getFont());
    cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    cpuInfoTextBox.draw(disp.getWindow());

    std::string Host = "Host: " + _osName + "\n";


    Display::TextBox modelTextBox(sf::Vector2f(10, 10), Host, disp.getFont());
    modelTextBox.setPosition(vecCalc(container.getPosition(), 20, 50));
    modelTextBox.draw(disp.getWindow());

}
