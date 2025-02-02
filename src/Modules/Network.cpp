/*
** EPITECH PROJECT, 2025
** src/Modules/Network
** File description:
** Network
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <dirent.h>

#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "Modules/Network.hpp"
#include "Utils.hpp"

Krell::Modules::Network::Network() : IModule(sf::Vector2f(400, 300), "Network"), _bytesSent(0), _bytesReceived(0), _packetsSent(0), _packetsReceived(0), _up(false)
{

}

Krell::Modules::Network::~Network()
{

}

void Krell::Modules::Network::refresh()
{
    _bytesSent = 0;
    _bytesReceived = 0;
    _packetsSent = 0;
    _packetsReceived = 0;
    _up = false;

    auto dir = opendir("/sys/class/net/");
    if (!dir) {
        std::cerr << "Failed to open /sys/class/net/" << std::endl;
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] != '.') {
            std::string path = "/sys/class/net/";
            path += entry->d_name;
            path += "/operstate";
            std::ifstream file(path);
            if (!file.is_open()) {
                continue;
            }
            std::string state;
            file >> state;
            if (state == "up") {
                _up = true;
                break;
            }
        }
    }
    closedir(dir);
    std::ifstream file("/proc/net/dev");
    if (!file.is_open()) {
        std::cerr << "failed to get network info" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string iface;
        ss >> iface;

        if (iface == "lo:") continue;
        if (iface.back() == ':') {
            iface.pop_back();
        }
        // Format de /proc/net/dev:
        size_t bytes, packets, errs, drop, fifo, frame, compressed, multicast;
        ss >> bytes;
        _bytesReceived += bytes;
        ss >> packets;
        _packetsReceived += packets;
        ss >> errs >> drop >> fifo >> frame >> compressed >> multicast;
        ss >> bytes;
        _bytesSent += bytes;
        ss >> packets;
        _packetsSent += packets;
    }
    file.close();
}

double Krell::Modules::Network::getValue(ModuleKey key) const {
    if (key == BYTES_SENT)
        return static_cast<double>(_bytesSent);
    if (key == BYTES_RECEIVED)
        return static_cast<double>(_bytesReceived);
    if (key == PACKETS_SENT)
        return static_cast<double>(_packetsSent);
    if (key == PACKETS_RECEIVED)
        return static_cast<double>(_packetsReceived);
    if (key == UP)
        return _up ? 1.0 : 0.0;
    return 0.0;
}

void Krell::Modules::Network::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(950, 50), size);
    container.draw(disp.getWindow());

    auto formatBytes = [](double bytes) -> std::string {
        if (bytes < 1024) return std::to_string(static_cast<int>(bytes)) + " B";
        if (bytes < 1024 * 1024) return std::to_string(static_cast<int>(bytes / 1024)) + " KB";
        return std::to_string(static_cast<int>(bytes / (1024 * 1024))) + " MB";
    };

    Display::TextBox titleBox(sf::Vector2f(360, 30), "Network Information", disp.getFont());
    titleBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    titleBox.draw(disp.getWindow());

    std::string status = "Status: " + std::string(_up ? "CONNECTED" : "DISCONNECTED");
    Display::TextBox statusBox(sf::Vector2f(360, 30), status, disp.getFont());
    statusBox.setPosition(vecCalc(container.getPosition(), 20, 70));
    statusBox.draw(disp.getWindow());

    std::string downloadInfo = "v Download\n";
    downloadInfo += "Bytes: " + formatBytes(getValue(IModule::BYTES_RECEIVED)) + "\n";
    downloadInfo += "Packets: " + std::to_string(static_cast<int>(getValue(IModule::PACKETS_RECEIVED)));
    Display::TextBox downloadBox(sf::Vector2f(360, 60), downloadInfo, disp.getFont());
    downloadBox.setPosition(vecCalc(container.getPosition(), 20, 120));
    downloadBox.draw(disp.getWindow());

    std::string uploadInfo = "^ Upload\n";
    uploadInfo += "Bytes: " + formatBytes(getValue(IModule::BYTES_SENT)) + "\n";
    uploadInfo += "Packets: " + std::to_string(static_cast<int>(getValue(IModule::PACKETS_SENT)));
    Display::TextBox uploadBox(sf::Vector2f(360, 60), uploadInfo, disp.getFont());
    uploadBox.setPosition(vecCalc(container.getPosition(), 20, 200));
    uploadBox.draw(disp.getWindow());
}
