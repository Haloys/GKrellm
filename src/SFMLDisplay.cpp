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
    _window.create(sf::VideoMode(1600, 1024), "MyGKrellm");
    _window.setFramerateLimit(60);
    _isRunning = true;
}

void Krell::SFMLDisplay::refresh()
{
    static sf::Clock clock;

    _window.clear(BG_COLOR);

    if (clock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        for (const auto &[name, module] : _modules)
        {
            module->refresh();
        }
        refresh_all();
    }

    Display::Container container(sf::Vector2f(0, 0), sf::Vector2f(200, 100));
    Display::Box box(container.getSize());
    Display::ProgressBar progressBar(sf::Vector2f(200, 50));

    sf::Font font;
    if (!font.loadFromFile(FONT_PATH))
    {
        std::cerr << "Error loading font\n";
    }

    // CPU Usage
    Display::TextBox cpuTextBox(sf::Vector2f(20, 20), "CPU Usage", font);
    cpuTextBox.setPosition(vecCalc(container.getPosition(), 50, 70));
    cpuTextBox.draw(_window);
    progressBar.setProgress(_modules["cpu_usage"]->getValue("usedPercent"));
    progressBar.setPosition(vecCalc(container.getPosition(), 50, 100));
    progressBar.draw(_window);

    Display::Chart chart(container.getSize());
    chart.setPosition(vecCalc(container.getPosition(), 50, 160));
    static std::vector<float> values(10, 0);
    if (clock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        values.erase(values.begin());
        values.push_back(_modules["cpu_usage"]->getValue("usedPercent"));
    }
    chart.setData({values});
    chart.draw(_window);

    // Detailed CPU Info
    Display::TextBox cpuInfoTextBox(sf::Vector2f(20, 20), "CPU Info", font);
    cpuInfoTextBox.setPosition(vecCalc(container.getPosition(), 50, 300));
    cpuInfoTextBox.draw(_window);

    std::string cpuInfo = "Cores: " + std::to_string(_modules["cpu_info"]->getValue("cores")) + "\n";
    cpuInfo += "Frequency: " + std::to_string(_modules["cpu_info"]->getValue("frequency")) + " MHz\n";
    cpuInfo += "Temperature: " + std::to_string(_modules["cpu_info"]->getValue("temperature")) + " °C\n";

    Display::TextBox cpuDetailsTextBox(sf::Vector2f(20, 20), cpuInfo, font);
    cpuDetailsTextBox.setPosition(vecCalc(container.getPosition(), 50, 330));
    cpuDetailsTextBox.draw(_window);

    // Memory Usage
    container.setPosition(sf::Vector2f(200, 0));

    Display::TextBox ramTextBox(sf::Vector2f(20, 20), "RAM Usage", font);
    ramTextBox.setPosition(sf::Vector2f(400, 70));
    ramTextBox.draw(_window);
    progressBar.setProgress(_modules["mem"]->getValue("usedPercent"));
    progressBar.setPosition(sf::Vector2f(400, 100));
    progressBar.draw(_window);

    // Refresh Delay
    Display::TextBox delayTextBox(sf::Vector2f(20, 20), "Refresh Delay: " + std::to_string(_refreshDelay) + "ms", font);
    delayTextBox.setPosition(sf::Vector2f(700, 70));
    delayTextBox.draw(_window);

    Display::ClockDisplay clockDisplay(sf::Vector2f(200, 50), sf::Vector2f(1500, 0));
    clockDisplay.update();
    clockDisplay.draw(_window);
    if (clock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        clock.restart();
    }
    _window.display();
}

void Krell::SFMLDisplay::stop()
{
    _window.close();
    _isRunning = false;
}

void Krell::SFMLDisplay::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _isRunning = false;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
            {
                _refreshDelay = std::min(10000, _refreshDelay + 100);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                _refreshDelay = std::max(100, _refreshDelay - 100);
            }
        }
    }
}

bool Krell::SFMLDisplay::isRunning() const
{
    return _isRunning;
}
