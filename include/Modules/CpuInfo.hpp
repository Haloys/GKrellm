/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/Modules/CpuInfo
** File description:
** cpu module
*/

#pragma once

#include "IModule.hpp"
#include <string>
#include <map>

namespace Krell {
    namespace Modules {
        class CpuInfo: public IModule {
            public:
                CpuInfo();
                ~CpuInfo();
                void refresh() override;
                double getValue(const std::string& key) const override { return 0; };
                std::string ModelName() const { return _cpuInfo.at("model name"); }
                std::string VendorId() const { return _cpuInfo.at("vendor_id"); }
                std::string CpuFamily() const { return _cpuInfo.at("cpu family"); }
                size_t CpuCores() const { return std::stoul(_cpuInfo.at("cpu cores")); }
                size_t CpuThreads() const { return std::stoul(_cpuInfo.at("siblings")); }
                size_t CpuMhz() const { return std::stoul(_cpuInfo.at("cpu MHz")); }
                std::string CacheSize() const { return _cpuInfo.at("cache size"); }
            private:
                std::map<std::string, std::string> _cpuInfo;
        };
    }
}
