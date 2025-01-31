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

                size_t usedPercent() const { return (used * 100) / total; }
                size_t freePercent() const { return (free * 100) / total; }
                CpuUsage();
                ~CpuUsage();
                void refresh();
            private:

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
