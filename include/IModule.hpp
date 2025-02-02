/*
** EPITECH PROJECT, 2025
** Include/IModule
** File description:
** IModule
*/

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>

namespace Krell {
    class SFMLDisplay;
    class IModule {
        public:
            enum ModuleKey {
                CORES,
                THREADS,
                MGHZ,
                TOTAL,
                USED,
                FREE,
                USEDPERCENT,
                FREEPERCENT,
                AVAILABLE,
                AVAILABLEPERCENT,
                SWAP_TOTAL,
                SWAP_USED,
                SWAP_PERCENT,
                TEMPERATURE,
                BYTES_SENT,
                BYTES_RECEIVED,
                PACKETS_SENT,
                PACKETS_RECEIVED,
                UP,
            };
            virtual ~IModule() = default;
            virtual void refresh() = 0;
            virtual double getValue(ModuleKey key) const = 0;

            IModule(sf::Vector2f p, sf::Vector2f s, const std::string& name) : pos(p), size(s), _name(name) {}
            sf::Vector2f pos;
            sf::Vector2f size;

            void disable() {
                _enabled = false;
            }
            void enable() {
                _enabled = true;
            }
            void toggle() {
                _enabled = !_enabled;
            }
            bool isEnabled() {
                return _enabled;
            }
            std::string getName() const { return _name; }
            void setName(const std::string& name) { _name = name; }
            virtual void drawModule(SFMLDisplay &disp) = 0;
        private:
            bool _enabled = true;
            std::string _name;
    };
}
