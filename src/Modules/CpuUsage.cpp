/*
** EPITECH PROJECT, 2025
** src/Modules/CpuUsage
** File description:
** CpuUsage
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "Modules/CpuUsage.hpp"
#include "IModule.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"

Krell::Modules::CpuUsage::CpuUsage()
{
    refresh();
}

Krell::Modules::CpuUsage::~CpuUsage()
{
}

void Krell::Modules::CpuUsage::refresh()
{
    std::ifstream file("/proc/stat");
    std::string line;

    if (!std::getline(file, line)) {
        std::cerr << "Failed to read /proc/stat" << std::endl;
        return;
    }
    std::istringstream ss(line);
    std::string cpu;
    ss >> cpu;
    ss >> _user >> _nice >> _system >> _idle >> _iowait >> _irq >> _softirq;

    _total = _user + _nice + _system + _idle + _iowait + _irq + _softirq;
    _used = _total - _idle;
    _free = _idle;

    if (total - _total == 0) {
        return;
    }
    usedPercent = 100 * (_used - used) / (_total - total);
    freePercent = 100 * (_free - free) / (_total - total);

    total = _total;
    used = _used;
    free = _free;
}

double Krell::Modules::CpuUsage::getValue(ModuleKey key) const
{
    switch (key) {
        case TOTAL:
            return static_cast<double>(total);
        case USED:
            return static_cast<double>(used);
        case FREE:
            return static_cast<double>(free);
        case USEDPERCENT:
            return static_cast<double>(usedPercent);
        case FREEPERCENT:
            return static_cast<double>(freePercent);
        default:
            return 0.0;
    }
}


void Krell::Modules::CpuUsage::drawModule(SFMLDisplay &disp)
{
    // Display::Container container(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
    // Display::ProgressBar progressBar(sf::Vector2f(360, 50), getFont());

    // // CPU Usage
    // container.setPosition(sf::Vector2f(50, 50));
    // container.setSize(sf::Vector2f(400, 400));
    // container.draw(getWindow());
    // Display::TextBox cpuTextBox(sf::Vector2f(20, 20), "CPU Usage", getFont());
    // cpuTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    // cpuTextBox.draw(getWindow());
    // progressBar.setPosition(vecCalc(container.getPosition(), 20, 60));
    // progressBar.setProgress(_modules["cpu_usage"]->getValue(IModule::USEDPERCENT), true);
    // progressBar.draw(getWindow());

    // Display::Chart chart(sf::Vector2f(360, 150));
    // chart.setPosition(vecCalc(container.getPosition(), 20, 120));
    // static std::vector<float> values(10, 0);
    // if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    // {
    //     values.erase(values.begin());
    //     values.push_back(_modules["cpu_usage"]->getValue(IModule::USEDPERCENT));
    // }
    // chart.setData({values}, true);
    // chart.draw(getWindow());

    // // Detailed CPU Info
    // Display::TextBox cpuInfoTextBox(sf::Vector2f(20, 20), "CPU Info", getFont());
    // cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 20, 280));
    // cpuInfoTextBox.draw(getWindow());

    // std::string cpuInfo = "Cores: " + std::to_string(int(_modules["cpu_info"]->getValue(IModule::CORES))) + "\n";
    // cpuInfo += "Frequency: " + std::to_string(int(_modules["cpu_info"]->getValue(IModule::MGHZ))) + " MHz\n";
    // /* cpuInfo += "Temperature: " + std::to_string(_modules["cpu_info"]->getValue(temp)) + " °C\n"; */

    // Display::TextBox cpuDetailsTextBox(sf::Vector2f(20, 20), cpuInfo, getFont());
    // cpuDetailsTextBox.setPosition(vecCalc(container.getPosition(), 20, 320));
    // cpuDetailsTextBox.draw(getWindow());
}