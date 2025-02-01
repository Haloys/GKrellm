/*
** EPITECH PROJECT, 2025
** Include/IDisplay
** File description:
** IDisplay
*/

#pragma once

#include "Modules/CpuUsage.hpp"
#include "Modules/CpuInfo.hpp"
#include "Modules/MemoryInfo.hpp"
#include <map>
#include <string>
#include <vector>


namespace Krell {
    class IDisplay {
        public:
            IDisplay() {
                _modules["cpu_usage"] = new Krell::Modules::CpuUsage();
                _modules["mem"] = new Krell::Modules::MemoryInfo();
                _modules["cpu_info"] = new Krell::Modules::CpuInfo();
            };
            void refresh_all() {
                for (auto& [key, value] : _modules) {
                    value->refresh();
                }
            }
            virtual ~IDisplay() {
                for (auto& [key, value] : _modules) {
                    delete value;
                }
            }
            virtual void refresh() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual bool isRunning() const = 0;
            virtual void handleEvents() = 0;
            virtual void drawModule(const IModule& module) = 0;
        protected:
            std::map<std::string, IModule *> _modules;
        };
}
