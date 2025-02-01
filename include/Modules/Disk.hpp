/*
** EPITECH PROJECT, 2025
** /home/vj/coding/t2r3/include/Modules/Disk
** File description:
** disk info mostly just disk usage
*/

#pragma once

#include <fstream>

#include "IModule.hpp"

namespace Krell {
    namespace Modules {
        class Disk: public IModule {
            public:
                Disk();
                ~Disk() override;
                void refresh() override;
                double getValue(ModuleKey) const override;

                size_t getUsed() const { return _used; }
                size_t getFree() const { return _free; }
                size_t getTotal() const { return _total; }
                size_t getUsedPercent() const { return _usedPercent; }
                size_t getFreePercent() const { return _freePercent; }

            private:
                size_t _used;
                size_t _free;
                size_t _total;
                size_t _usedPercent;
                size_t _freePercent;
        };
    }
}
