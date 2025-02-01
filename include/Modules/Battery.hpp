/*
** EPITECH PROJECT, 2025
** /home/vj/coding/t2r3/include/Modules/Battery
** File description:
** Batter
*/

#pragma once

#include <cstddef>

#include "IModule.hpp"

namespace Krell {
    namespace Modules {
        class Battery: public IModule {
            public:
                Battery();
                ~Battery() override;
                void refresh() override;
                double getValue(ModuleKey) const override;

                size_t getBatteryPercent() const { return _batteryPercent; }
                size_t getBatteryTime() const { return _batteryTime; }
                bool isCharging() const { return _charging; }

            private:
                size_t _batteryPercent;
                size_t _batteryTime;
                bool _charging;
        };
    }
}
