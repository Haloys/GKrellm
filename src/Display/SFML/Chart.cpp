/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** Chart
*/

#include "SFMLDisplay.hpp"
#include "Display/SFML/Chart.hpp"

namespace Display
{
    Chart::Chart(sf::Vector2f size) : _size(size)
    {
        _background.setSize(size);
        _background.setFillColor(BOX_COLOR);
    }

    void Chart::setPosition(sf::Vector2f position)
    {
        _background.setPosition(position);
        for (auto& bar : _bars) {
            bar.setPosition(position);
        }
    }

    void Chart::setData(const std::vector<float>& data)
    {
        _bars.clear();
        float barWidth = (_size.x - 20) / data.size();
        for (size_t i = 0; i < data.size(); ++i) {
            sf::RectangleShape bar;
            float barHeight = (data[i] / 100.0f) * (_size.y - 20);
            bar.setSize(sf::Vector2f(barWidth - 2, barHeight));
            bar.setFillColor(BAR_COLOR_GREEN);
            bar.setPosition(_background.getPosition().x + 10 + i * barWidth, _background.getPosition().y + (_size.y - 10 - barHeight));
            _bars.push_back(bar);
        }
    }

    void Chart::draw(sf::RenderWindow &window)
    {
        window.draw(_background);
        for (const auto& bar : _bars) {
            window.draw(bar);
        }
    }
}
