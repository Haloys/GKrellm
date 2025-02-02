/*
** EPITECH PROJECT, 2025
** src/Modules/DateTimeInfo
** File description:
** DateTimeInfo
*/

#include <ctime>
#include <iomanip>
#include "Display/SFML/Container.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Utils.hpp"

#include "Modules/DateTimeInfo.hpp"

Krell::Modules::DateTimeInfo::DateTimeInfo() : IModule(sf::Vector2f(0, 0))
{
    refresh();
}

void Krell::Modules::DateTimeInfo::refresh()
{
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    _currentDateTime = buffer;
}

double Krell::Modules::DateTimeInfo::getValue(ModuleKey key) const
{
    (void)key;
    return 0.0;
}

void Krell::Modules::DateTimeInfo::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(350, 700), size);

    container.draw(disp.getWindow());

    Display::TextBox cpuInfoTextBox(sf::Vector2f(10, 10), "date", disp.getFont());
    cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 0, 0));
    cpuInfoTextBox.draw(disp.getWindow());



    Display::TextBox modelTextBox(sf::Vector2f(10, 10), _currentDateTime, disp.getFont());
    modelTextBox.setPosition(vecCalc(container.getPosition(), 10, 20));
    modelTextBox.draw(disp.getWindow());

}
