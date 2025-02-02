/*
** EPITECH PROJECT, 2025
** src/Modules/Disk
** File description:
** Disk
*/

#include <fstream>
#include <sstream>

#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "Modules/HostInfo.hpp"
#include "Modules/CpuUsage.hpp"
#include "Modules/Disk.hpp"
#include "IModule.hpp"
#include "Utils.hpp"

Krell::Modules::Disk::Disk() : IModule(sf::Vector2f(400, 200), "Disk"), _used(0), _free(0), _total(0), _usedPercent(0), _freePercent(0)
{
    refresh();
}

Krell::Modules::Disk::~Disk()
{

}

void Krell::Modules::Disk::refresh()
{
    struct statvfs disk_info;
    if (statvfs("/", &disk_info) == 0) {
        unsigned long blocksize = disk_info.f_bsize;
        _total = blocksize * disk_info.f_blocks;
        _free = blocksize * disk_info.f_bfree;
        _used = _total - _free;

        if (_total > 0) {
            _usedPercent = static_cast<double>(_used * 100) / _total;
            _freePercent = static_cast<double>(_free * 100) / _total;
        } else {
            _usedPercent = 0;
            _freePercent = 0;
        }
    } else {
        _total = 0;
        _free = 0;
        _used = 0;
        _usedPercent = 0;
        _freePercent = 0;
    }
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

void Krell::Modules::Disk::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(950, 600), size);
    container.draw(disp.getWindow());

    Display::TextBox titleBox(sf::Vector2f(360, 30), "Disk Information", disp.getFont());
    titleBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    titleBox.draw(disp.getWindow());

    std::string diskInfo = "Total Disk Space: " + std::to_string(_total / (1024 * 1024 * 1024)) + " GB\n";
    diskInfo += "Used Disk Space: " + std::to_string(_used / (1024 * 1024 * 1024)) + " GB (" + std::to_string(_usedPercent) + "%)\n";
    diskInfo += "Free Disk Space: " + std::to_string(_free / (1024 * 1024 * 1024)) + " GB (" + std::to_string(_freePercent) + "%)\n";

    Display::TextBox infoBox(sf::Vector2f(360, 90), diskInfo, disp.getFont());
    infoBox.setPosition(vecCalc(container.getPosition(), 20, 70));
    infoBox.draw(disp.getWindow());
}
