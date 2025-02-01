/*
** EPITECH PROJECT, 2025
** Include/Modules/HostInfo
** File description:
** HostInfo
*/

#pragma once

#include <string>
#include <unistd.h>

#include "IModule.hpp"

namespace Krell {
    namespace Modules {
        class HostInfo: public IModule {
            public:
                HostInfo();
                ~HostInfo() override = default;
                void refresh() override;
                double getValue(ModuleKey key) const override;

                std::string getHostname() const { return _hostname; }
                std::string getUsername() const { return _username; }
                virtual void drawModule(SFMLDisplay &disp) override {};

            private:
                std::string _hostname;
                std::string _username;
                void refreshHostname();
                void refreshUsername();
        };
    }
}
