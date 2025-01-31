/*
** EPITECH PROJECT, 2025
** Include/IDisplay
** File description:
** IDisplay
*/

#pragma once

namespace Krell {
    class IDisplay {
        public:
            virtual ~IDisplay() = default;
            virtual void refresh() = 0;
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual bool isRunning() const = 0;
            virtual void handleEvents() = 0;
        };
}
