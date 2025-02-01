/*
** EPITECH PROJECT, 2025
** Include/Modules/CpuInfo
** File description:
** CpuInfo
*/

#pragma once

#include <string>
#include <map>

#include "IModule.hpp"

namespace Krell {
    class SFMLDisplay;
}

namespace Krell {
    namespace Modules {
        class CpuInfo: public IModule {
            public:
                CpuInfo();
                ~CpuInfo();
                void refresh() override;
                double getValue(ModuleKey key) const override;
                std::string ModelName() const { return _cpuInfo.at("model name"); }
                std::string VendorId() const { return _cpuInfo.at("vendor_id"); }
                std::string CpuFamily() const { return _cpuInfo.at("cpu family"); }
                size_t CpuCores() const { return std::stoul(_cpuInfo.at("cpu cores")); }
                size_t CpuThreads() const { return std::stoul(_cpuInfo.at("siblings")); }
                size_t CpuMhz() const { return std::stoul(_cpuInfo.at("cpu MHz")); }
                std::string CacheSize() const { return _cpuInfo.at("cache size"); }
                void drawModule(SFMLDisplay &disp) override;

            private:
                std::map<std::string, std::string> _cpuInfo;
        };
    }
}
