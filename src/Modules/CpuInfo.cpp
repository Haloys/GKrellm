/*
** EPITECH PROJECT, 2025
** src/Modules/CpuInfo
** File description:
** CpuInfo
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "Modules/CpuInfo.hpp"
#include "IModule.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "Utils.hpp"

Krell::Modules::CpuInfo::CpuInfo() : IModule(sf::Vector2f(400, 200))
{
    refresh();
}

Krell::Modules::CpuInfo::~CpuInfo()
{

}

void Krell::Modules::CpuInfo::refresh()
{
    std::ifstream file("/proc/cpuinfo");

    if (!file.is_open()) {
        return;
    }
    std::string line;
    std::string key;
    std::string value;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::getline(ss, key, ':');
        std::getline(ss, value);
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        _cpuInfo[key] = value;
    }
    file.close();

    //temperature
    file.open("/sys/class/thermal/thermal_zone0/temp");
    std::getline(file, _cpuInfo["Temperature"]);
}

double Krell::Modules::CpuInfo::getValue(ModuleKey key) const
{
    if (key == CORES)
        return static_cast<double>(CpuCores());
    if (key == THREADS)
        return static_cast<double>(CpuThreads());
    if (key == MGHZ)
        return static_cast<double>(CpuMhz());
    if (key == TEMPERATURE)
        return (std::stof(_cpuInfo.at("Temperature"))) / 1000;
    return 0.0;
}

void Krell::Modules::CpuInfo::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(50, 370), size);
    Display::ProgressBar progressBar(sf::Vector2f(360, 50), disp.getFont());

    container.draw(disp.getWindow());

    Display::TextBox cpuInfoTextBox(sf::Vector2f(20, 20), "CPU Info", disp.getFont());
    cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    cpuInfoTextBox.draw(disp.getWindow());

    std::string modelName = _cpuInfo["model name"] + "\n";
    modelName += "Cores: " + std::to_string(int(getValue(IModule::CORES))) + "\n";
    modelName += "Threads: " + std::to_string(int(getValue(IModule::THREADS))) + "\n";
    modelName += "Frequency: " + std::to_string(int(getValue(IModule::MGHZ))) + " MHz\n";
    // modelName += "Temperature: " + std::to_string(int(getValue(IModule::TEMPERATURE))) + "C\n";

    Display::TextBox modelTextBox(sf::Vector2f(20, 20), modelName, disp.getFont());
    modelTextBox.setPosition(vecCalc(container.getPosition(), 20, 50));
    modelTextBox.draw(disp.getWindow());
}
