/*
** EPITECH PROJECT, 2025
** /tmp/playground/r3/include/IDisplay
** File description:
** Display interface
*/

#pragma once

namespace Krell {
    class IDisplay {
        public:
            virtual ~IDisplay() = default;
            virtual void refresh() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
    };
}
