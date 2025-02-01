/*
** EPITECH PROJECT, 2025
** Include/IModule
** File description:
** IModule
*/

#pragma once

#include <string>

#include "SFMLDisplay.hpp"

namespace Krell {
    class SFMLDisplay;
}

namespace Krell {
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
            };
            virtual ~IModule() = default;
            virtual void refresh() = 0;
            virtual double getValue(ModuleKey key) const = 0;
            virtual void drawModule(SFMLDisplay &disp) = 0;
    };
}
