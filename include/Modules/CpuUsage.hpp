/*
** EPITECH PROJECT, 2025
** Include/Modules/CpuUsage
** File description:
** CpuUsage
*/

#pragma once

#include <string>

#include "SFMLDisplay.hpp"
#include "IModule.hpp"

namespace Krell {
    class SFMLDisplay;
}

namespace Krell {
    namespace Modules {
        class CpuUsage: public IModule {
            public:
                double total;
                double used;
                double free;

                double usedPercent = 0;
                double freePercent = 0;
                CpuUsage();
                ~CpuUsage();
                void refresh() override;
                double getValue(ModuleKey) const override;

                void drawModule(SFMLDisplay &disp) override;
            private:
                time_t _lastRefresh;

                double _user;
                double _nice;
                double _system;
                double _idle;
                double _iowait;
                double _irq;
                double _softirq;

                double _total;
                double _used;
                double _free;
        };
    }
}
