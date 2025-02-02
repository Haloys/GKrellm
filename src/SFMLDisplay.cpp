/*
** EPITECH PROJECT, 2025
** Src/SFMLDisplay
** File description:
** SFMLDisplay
*/

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "SFMLDisplay.hpp"
#include "Utils.hpp"
#include "Display/SFML/ClockDisplay.hpp"
#include "Display/SFML/TextBox.hpp"

Krell::SFMLDisplay::SFMLDisplay() : IDisplay(), _isRunning(false), _refreshDelay(100), _isMenuOpen(false)
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
    int yOffset[3] = {60, 60, 60};
    int column = 0;

    for (const auto &[name, module] : _modules)
    {
        if (module->isEnabled())
        {
            module->pos = sf::Vector2f(50 + column * 500, yOffset[column]);
            module->drawModule(*this);
            yOffset[column] += module->size.y + 10;
            column = (column + 1) % 3;
        }
    }

    sf::RectangleShape button(sf::Vector2f(100, 30));
    button.setPosition(sf::Vector2f(1500, 10));
    button.setFillColor(sf::Color::Blue);
    getWindow().draw(button);

    sf::Text buttonText("Modules", getFont(), 20);
    buttonText.setPosition(sf::Vector2f(1510, 10));
    getWindow().draw(buttonText);

    if (_isMenuOpen)
    {
        sf::RectangleShape menu(sf::Vector2f(200, 300));
        menu.setPosition(sf::Vector2f(1400, 50));
        menu.setFillColor(sf::Color(50, 50, 50, 200));
        getWindow().draw(menu);

        int yOffset = 60;
        for (const auto &[name, module] : _modules)
        {
            sf::Text moduleText(name + ": " + (module->isEnabled() ? "Enabled" : "Disabled"), getFont(), 20);
            moduleText.setPosition(sf::Vector2f(1410, yOffset));
            getWindow().draw(moduleText);
            yOffset += 30;
        }
    }
}

void Krell::SFMLDisplay::refresh()
{
    getWindow().clear(BG_COLOR);

    if (_delayClock.getElapsedTime().asMilliseconds() > _refreshDelay)
    {
        refresh_all();
    }

    for (const auto &[name, module] : _modules)
    {
        if (module->isEnabled())
            module->drawModule(*this);
    }

    // Refresh Delay
    Display::TextBox delayTextBox(sf::Vector2f(20, 20), "Refresh Delay: " + std::to_string(_refreshDelay) + "ms", getFont());
    delayTextBox.setPosition(sf::Vector2f(680, 70));
    delayTextBox.draw(getWindow());

    drawModule();

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
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                _refreshDelay = std::min(10000, _refreshDelay + 100);
                break;
            case sf::Keyboard::Down:
                _refreshDelay = std::max(100, _refreshDelay - 100);
                break;
            case sf::Keyboard::C:
                _modules["cpu_usage"]->toggle();
                break;
            case sf::Keyboard::R:
                _modules["mem"]->toggle();
                break;
            case sf::Keyboard::I:
                _modules["cpu_info"]->toggle();
                break;
            case sf::Keyboard::D:
                _modules["datetime"]->toggle();
                break;
            case sf::Keyboard::H:
                _modules["host"]->toggle();
                break;
            case sf::Keyboard::O:
                _modules["os"]->toggle();
                break;
            case sf::Keyboard::N:
                _modules["network"]->toggle();
                break;
            case sf::Keyboard::B:
                _modules["battery"]->toggle();
                break;

            default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(getWindow());
                if (mousePos.x >= 1500 && mousePos.x <= 1600 && mousePos.y >= 10 && mousePos.y <= 40)
                {
                    _isMenuOpen = !_isMenuOpen;
                }
                else if (_isMenuOpen && mousePos.x >= 1400 && mousePos.x <= 1600 && mousePos.y >= 50 && mousePos.y <= 350)
                {
                    int index = (mousePos.y - 50) / 30;
                    auto it = _modules.begin();
                    std::advance(it, index);
                    if (it != _modules.end())
                    {
                        it->second->toggle();
                    }
                }
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
