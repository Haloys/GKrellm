/*
** EPITECH PROJECT, 2025
** Include/IDisplay
** File description:
** IDisplay
*/

#pragma once

#include "IModule.hpp"
#include "Modules/CpuUsage.hpp"
#include "Modules/CpuInfo.hpp"
#include "Modules/MemoryInfo.hpp"
#include <map>
#include <string>

namespace Krell {
    class IDisplay {
        public:
            IDisplay() {
                _modules["cpu_usage"] = Krell::Modules::CpuUsage();
                _modules["mem"] = Krell::Modules::MemoryInfo();
                _modules["cpu_info"] = Krell::Modules::CpuUsage();
            };
            virtual ~IDisplay() = default;
            virtual void refresh() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual bool isRunning() const = 0;
            virtual void handleEvents() = 0;
        protected:
            std::map<std::string, IModule> _modules;
        };
}
