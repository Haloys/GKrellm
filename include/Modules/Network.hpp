/*
** EPITECH PROJECT, 2025
** Include/Modules/Network
** File description:
** Network
*/

#pragma once

#include <cstddef>

#include "IModule.hpp"

namespace Krell {
    namespace Modules {
        class Network: public IModule {
            public:
                Network();
                ~Network() override;
                void refresh() override;
                double getValue(ModuleKey) const override;

                size_t getBytesSent() const { return _bytesSent; }
                size_t getBytesReceived() const { return _bytesReceived; }
                size_t getPacketsSent() const { return _packetsSent; }
                size_t getPacketsReceived() const { return _packetsReceived; }

                bool up() const { return _up; }

                void drawModule(SFMLDisplay &disp) override;

            private:
                size_t _bytesSent;
                size_t _bytesReceived;
                size_t _packetsSent;
                size_t _packetsReceived;
                bool _up;
        };
    }
}
