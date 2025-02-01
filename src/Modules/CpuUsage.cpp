/*
** EPITECH PROJECT, 2025
** src/Modules/CpuUsage
** File description:
** CpuUsage
*/

#include <iomanip>
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
#include "Utils.hpp"

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
    _used = _user + _nice + _system + _irq + _softirq;
    _free = _idle + _iowait;



    if (total - _total == 0) {
        return;
    }
    double usd = _used - used;

    usedPercent = 100 * usd / (_total - total);
    freePercent = 100 - usedPercent;

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
    Display::Container container(sf::Vector2f(50, 50), sf::Vector2f(400, 290));
    Display::ProgressBar progressBar(sf::Vector2f(360, 50), disp.getFont());

    container.draw(disp.getWindow());
    Display::TextBox cpuTextBox(sf::Vector2f(20, 20), "CPU Usage", disp.getFont());
    cpuTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    cpuTextBox.draw(disp.getWindow());
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 60));
    progressBar.setProgress(disp.getModule("cpu_usage")->getValue(IModule::USEDPERCENT), true);
    progressBar.draw(disp.getWindow());

    Display::Chart chart(sf::Vector2f(360, 150));
    chart.setPosition(vecCalc(container.getPosition(), 20, 120));
    static std::vector<float> values(10, 0);
    if (disp.getDelayClock().getElapsedTime().asMilliseconds() > disp.getRefreshDelay())
    {
        values.erase(values.begin());
        values.push_back(disp.getModule("cpu_usage")->getValue(IModule::USEDPERCENT));
    }
    chart.setData({values}, true);
    chart.draw(disp.getWindow());
}
