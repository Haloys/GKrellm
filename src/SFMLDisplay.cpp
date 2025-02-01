/*
** EPITECH PROJECT, 2025
** Src/SFMLDisplay
** File description:
** SFMLDisplay
*/

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>

#include "SFMLDisplay.hpp"
#include "Utils.hpp"
#include "Display/SFML/Box.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/Chart.hpp"
#include "Display/SFML/ClockDisplay.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/TextBox.hpp"
#include "IModule.hpp"

Krell::SFMLDisplay::SFMLDisplay() : IDisplay(), _isRunning(false), _refreshDelay(100)
{
}

Krell::SFMLDisplay::~SFMLDisplay()
{
    if (_isRunning)
    {
        stop();
    }
}

void Krell::SFMLDisplay::start()
{
    getWindow().create(sf::VideoMode(1600, 1024), "MyGKrellm");
    getWindow().setFramerateLimit(60);
    _isRunning = true;
    if (!getFont().loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font\n";
    }
}

void Krell::SFMLDisplay::drawModule()
{

}

void Krell::SFMLDisplay::refresh()
{
    getWindow().clear(BG_COLOR);

    if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        for (const auto &[name, module] : _modules)
        {
            module->refresh();
        }
        refresh_all();
    }

    Display::Container container(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
    Display::ProgressBar progressBar(sf::Vector2f(360, 50), getFont());

    // CPU Usage
    container.setPosition(sf::Vector2f(50, 50));
    container.setSize(sf::Vector2f(400, 400));
    container.draw(getWindow());
    Display::TextBox cpuTextBox(sf::Vector2f(20, 20), "CPU Usage", getFont());
    cpuTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    cpuTextBox.draw(getWindow());
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 60));
    progressBar.setProgress(_modules["cpu_usage"]->getValue(IModule::USEDPERCENT), true);
    progressBar.draw(getWindow());

    Display::Chart chart(sf::Vector2f(360, 150));
    chart.setPosition(vecCalc(container.getPosition(), 20, 120));
    static std::vector<float> values(10, 0);
    if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        values.erase(values.begin());
        values.push_back(_modules["cpu_usage"]->getValue(IModule::USEDPERCENT));
    }
    chart.setData({values}, true);
    chart.draw(getWindow());

    // Detailed CPU Info
    Display::TextBox cpuInfoTextBox(sf::Vector2f(20, 20), "CPU Info", getFont());
    cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 20, 280));
    cpuInfoTextBox.draw(getWindow());

    std::string cpuInfo = "Cores: " + std::to_string(int(_modules["cpu_info"]->getValue(IModule::CORES))) + "\n";
    cpuInfo += "Frequency: " + std::to_string(int(_modules["cpu_info"]->getValue(IModule::MGHZ))) + " MHz\n";
    /* cpuInfo += "Temperature: " + std::to_string(_modules["cpu_info"]->getValue(temp)) + " °C\n"; */

    Display::TextBox cpuDetailsTextBox(sf::Vector2f(20, 20), cpuInfo, getFont());
    cpuDetailsTextBox.setPosition(vecCalc(container.getPosition(), 20, 320));
    cpuDetailsTextBox.draw(getWindow());

    // Memory Usage
    container.setPosition(sf::Vector2f(500, 50));
    container.setSize(sf::Vector2f(400, 400));
    container.draw(getWindow());

    Display::TextBox ramTextBox(sf::Vector2f(20, 20), "RAM Usage", getFont());
    ramTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    ramTextBox.draw(getWindow());
    progressBar.setProgress(_modules["mem"]->getValue(IModule::USEDPERCENT), true);
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 60));
    progressBar.draw(getWindow());
    Display::TextBox ramSwapTextBox(sf::Vector2f(20, 20), "Swap Usage", getFont());
    ramSwapTextBox.setPosition(vecCalc(container.getPosition(), 20, 120));
    ramSwapTextBox.draw(getWindow());
    progressBar.setProgress(_modules["mem"]->getValue(IModule::USEDPERCENT), true);
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 160));
    progressBar.draw(getWindow());

    // Refresh Delay
    Display::TextBox delayTextBox(sf::Vector2f(20, 20), "Refresh Delay: " + std::to_string(_refreshDelay) + "ms", getFont());
    delayTextBox.setPosition(vecCalc(container.getPosition(), 700, 70));
    delayTextBox.draw(getWindow());

    Display::ClockDisplay clockDisplay(sf::Vector2f(200, 50), sf::Vector2f(1500, 0));
    clockDisplay.update();
    clockDisplay.draw(getWindow());
    if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        _delayClock.restart();
    }
    getWindow().display();
}

void Krell::SFMLDisplay::stop()
{
    getWindow().close();
    _isRunning = false;
}

void Krell::SFMLDisplay::handleEvents()
{
    sf::Event event;
    while (getWindow().pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _isRunning = false;
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Up)
            {
                _refreshDelay = std::min(10000, _refreshDelay + 100);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                _refreshDelay = std::max(100, _refreshDelay - 100);
            }
            break;
        default:
            break;
        }
    }
}

bool Krell::SFMLDisplay::isRunning() const
{
    return _isRunning;
}
