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
#include "Modules/DateTimeInfo.hpp"
#include "Utils.hpp"

Krell::Modules::DateTimeInfo::DateTimeInfo() : IModule(sf::Vector2f(400, 200), "DateTimeInfo")
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
    Display::Container container(sf::Vector2f(500, 480), size);

    container.draw(disp.getWindow());

    Display::TextBox dateTimeTextBox(sf::Vector2f(20, 20), "Date & Time", disp.getFont());
    dateTimeTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    dateTimeTextBox.draw(disp.getWindow());

    Display::TextBox timeTextBox(sf::Vector2f(20, 20), _currentDateTime, disp.getFont());
    timeTextBox.setPosition(vecCalc(container.getPosition(), 20, 50));
    timeTextBox.draw(disp.getWindow());
}
