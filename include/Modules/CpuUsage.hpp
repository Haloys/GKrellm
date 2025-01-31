/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/Modules/CpuUsage
** File description:
** cpu module
*/

#pragma once

#include "IModule.hpp"

#include <string>

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
                double getValue(const std::string& key) const override;
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
