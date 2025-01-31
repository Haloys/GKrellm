/*
** EPITECH PROJECT, 2025
** Include/IModule
** File description:
** IModule
*/

#pragma once

namespace Krell {
    class IModule {
        public:
            virtual ~IModule() = default;
            virtual void refresh() = 0;
    };
}
