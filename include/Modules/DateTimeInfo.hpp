/*
** EPITECH PROJECT, 2025
** Include/Modules/DateTimeInfo
** File description:
** DateTimeInfo
*/

#pragma once

#include <string>
#include <ctime>

#include "IModule.hpp"

namespace Krell {
    namespace Modules {
        class DateTimeInfo: public IModule {
            public:
                DateTimeInfo();
                ~DateTimeInfo() override = default;
                void refresh() override;
                double getValue(ModuleKey key) const override;

                std::string getCurrentDateTime() const { return _currentDateTime; }
                size_t getDateLength() const { return _currentDateTime.length(); }
                virtual void drawModule(SFMLDisplay &disp) override {};

            private:
                std::string _currentDateTime;
        };
    }
}
