/*
** EPITECH PROJECT, 2025
** Include/IModule
** File description:
** IModule
*/

#pragma once

#include <string>

namespace Krell {
    class IModule {
        public:
            bool enabled = true;
            virtual ~IModule() = default;
            virtual void refresh() = 0;
    };
}
