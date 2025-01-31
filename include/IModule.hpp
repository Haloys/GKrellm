/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/IDisplay
** File description:
** modules
*/

#pragma once

namespace Krell {
    class IModule {
        public:
            virtual ~IModule() = default;
            virtual void refresh() = 0;
    };
}
