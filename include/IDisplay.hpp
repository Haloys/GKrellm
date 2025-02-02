/*
** EPITECH PROJECT, 2025
** Include/IDisplay
** File description:
** IDisplay
*/

#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Modules/Battery.hpp"
#include "Modules/CpuUsage.hpp"
#include "Modules/CpuInfo.hpp"
#include "Modules/MemoryInfo.hpp"
#include "Modules/DateTimeInfo.hpp"
#include "Modules/HostInfo.hpp"
#include "Modules/OsInfo.hpp"
#include "Modules/Network.hpp"
#include "Modules/Disk.hpp"

namespace Krell {
    class IModule;
    namespace Modules {
        class CpuUsage;
        class CpuInfo;
        class MemoryInfo;
        class Network;
    }
}

namespace Krell {
    class IDisplay {
        public:
            IDisplay() {
                _modules["cpu_usage"] = std::make_unique<Modules::CpuUsage>();
                _modules["mem"] = std::make_unique<Modules::MemoryInfo>();
                _modules["cpu_info"] = std::make_unique<Modules::CpuInfo>();
                _modules["datetime"] = std::make_unique<Modules::DateTimeInfo>();
                _modules["host"] = std::make_unique<Modules::HostInfo>();
                _modules["os"] = std::make_unique<Modules::OsInfo>();
                _modules["network"] = std::make_unique<Modules::Network>();
                _modules["disk"] = std::make_unique<Modules::Disk>();
                _modules["battery"] = std::make_unique<Modules::Battery>();
            };
            virtual ~IDisplay() = default;
            void refresh_all() {
                for (auto& [key, value] : _modules) {
                    if (value->isEnabled())
                        value->refresh();
                }
            }
            virtual void refresh() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual bool isRunning() const = 0;
            virtual void handleEvents() = 0;
            virtual void drawModule() = 0;
        protected:
            std::map<std::string, std::unique_ptr<IModule>> _modules;
    };
};
