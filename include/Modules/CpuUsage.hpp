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
                size_t total;
                size_t used;
                size_t free;

                size_t usedPercent = 0;
                size_t freePercent = 0;
                CpuUsage();
                ~CpuUsage();
                void refresh() override;
                double getValue(const std::string& key) const override;
            private:
                time_t _lastRefresh;

                size_t _user;
                size_t _nice;
                size_t _system;
                size_t _idle;
                size_t _iowait;
                size_t _irq;
                size_t _softirq;

                size_t _total;
                size_t _used;
                size_t _free;
        };
    }
}
