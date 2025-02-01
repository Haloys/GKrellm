/*
** EPITECH PROJECT, 2025
** Include/IModule
** File description:
** IModule
*/

#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <SFML/Graphics.hpp>

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

            IModule(sf::Vector2f s) : size(s) {}
            sf::Vector2f size;

            void disable() {
                _enabled = false;
            }
            void enable() {
                _enabled = true;
            }
            bool isEnabled() {
                return _enabled;
            }
            virtual void drawModule(SFMLDisplay &disp) = 0;
        private:
            bool _enabled = true;
    };
}
