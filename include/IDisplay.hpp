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
#include "Modules/CpuUsage.hpp"
#include "Modules/CpuInfo.hpp"
#include "Modules/MemoryInfo.hpp"

namespace Krell {
    class IDisplay {
        public:
            IDisplay() {
                _modules["cpu_usage"] = std::make_unique<Modules::CpuUsage>();
                _modules["mem"] = std::make_unique<Modules::MemoryInfo>();
                _modules["cpu_info"] = std::make_unique<Modules::CpuInfo>();
            };
            virtual ~IDisplay() = default;
            void refresh_all() {
                for (auto& [key, value] : _modules) {
                    value->refresh();
                }
            }
            virtual void refresh() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual bool isRunning() const = 0;
            virtual void handleEvents() = 0;
            virtual void drawModule(const IModule& module) = 0;
        protected:
            std::map<std::string, std::unique_ptr<IModule>> _modules;
    };
};
