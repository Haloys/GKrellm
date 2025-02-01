/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/Modules/MemoryInfo
** File description:
** Memory Info
*/

#pragma once

#include "IModule.hpp"
#include <cstddef>
#include <map>
#include <string>

namespace Krell {
    namespace Modules {
        class MemoryInfo: public IModule {
            public:
                MemoryInfo();
                ~MemoryInfo();
                void refresh() override;

                // note that the values are in KB
                size_t Total() const { return _memoryInfo.at("MemTotal:"); }
                size_t Used() const { return _memoryInfo.at("MemTotal:") - _memoryInfo.at("MemFree:"); }
                size_t Free() const { return _memoryInfo.at("MemFree:"); }
                size_t Available() const { return _memoryInfo.at("MemAvailable:"); }

                size_t usePercentage() const { return (Used() * 100) / Total(); }
                size_t freePercentage() const { return (Free() * 100) / Total(); }
                size_t availablePercentage() const { return (Available() * 100) / Total(); }

                size_t SwapTotal() const { return _memoryInfo.at("SwapTotal:"); }
                size_t SwapUsed() const { return _memoryInfo.at("SwapTotal:") - _memoryInfo.at("SwapFree:"); }
                size_t swapUsePercentage() const { return (SwapUsed() * 100) / SwapTotal(); }

                size_t Buffers() const { return _memoryInfo.at("Buffers:"); }
                size_t Cached() const { return _memoryInfo.at("Cached:"); }

                size_t Active() const { return _memoryInfo.at("Active:"); }
                size_t Inactive() const { return _memoryInfo.at("Inactive:"); }

                size_t VmallocTotal() const { return _memoryInfo.at("VmallocTotal:"); }
                size_t VmallocUsed() const { return _memoryInfo.at("VmallocUsed:"); }
                size_t VmallocChunk() const { return _memoryInfo.at("VmallocChunk:"); }
                size_t vmallocUsePercentage() const { return (VmallocUsed() * 100) / VmallocTotal(); }
                size_t vmallocChunkPercentage() const { return (VmallocChunk() * 100) / VmallocTotal(); }
                size_t vmallocUsedPercentage() const { return (VmallocUsed() * 100) / VmallocTotal(); }


                double getValue(const std::string& key) const override { return 0; };

            private:
                std::map<std::string, size_t> _memoryInfo;
        };
    }
}
