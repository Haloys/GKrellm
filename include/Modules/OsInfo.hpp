/*
** EPITECH PROJECT, 2025
** Include/Modules/OsInfo
** File description:
** OsInfo
*/

#pragma once

#include <string>
#include <sys/utsname.h>

#include "IModule.hpp"

namespace Krell {
    namespace Modules {
        class OsInfo: public IModule {
            public:
                OsInfo();
                ~OsInfo() override = default;
                void refresh() override;
                double getValue(ModuleKey key) const override;

                std::string getOsName() const { return _osName; }
                std::string getKernelVersion() const { return _kernelVersion; }
                std::string getMachine() const { return _machine; }

            private:
                std::string _osName;
                std::string _kernelVersion;
                std::string _machine;
                void refreshOsInfo();
        };
    }
}