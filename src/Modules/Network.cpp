/*
** EPITECH PROJECT, 2025
** /home/vj/coding/t2r3/src/Modules/Network
** File description:
** ewfou
*/


#include <fstream>
#include <sstream>
#include <iostream>
#include <dirent.h>

#include "Modules/Network.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "Utils.hpp"

Krell::Modules::Network::Network() :
    IModule(sf::Vector2f(400, 430)),
    _bytesSent(0), _bytesReceived(0), _packetsSent(0), _packetsReceived(0), _up(false)
{
}

Krell::Modules::Network::~Network() {}

void Krell::Modules::Network::refresh() {
    _bytesSent = 0;
    _bytesReceived = 0;
    _packetsSent = 0;
    _packetsReceived = 0;
    _up = false;


    //check if network is up by checking if every directory in /sys/class/net/ has an operstate file
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
        if (iface.back() == ':') {
            iface.pop_back();
        }
        size_t bytesSent;
        size_t packetsSent;
        size_t bytesReceived;
        size_t packetsReceived;
        ss >> bytesReceived >> bytesReceived >> bytesReceived >> bytesReceived >> bytesSent >> packetsSent >> bytesReceived >> bytesReceived >> bytesReceived >> bytesReceived >> bytesReceived >> bytesReceived >> bytesReceived >> bytesReceived >> packetsReceived;
        _bytesSent += bytesSent;
        _bytesReceived += bytesReceived;
        _packetsSent += packetsSent;
        _packetsReceived += packetsReceived;
    }
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
    Display::ProgressBar progressBar(sf::Vector2f(360, 50), disp.getFont());

    container.draw(disp.getWindow());

    Display::TextBox bytesSentTextBox(sf::Vector2f(20, 20), "Bytes Sent", disp.getFont());
    bytesSentTextBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    bytesSentTextBox.draw(disp.getWindow());
    progressBar.setProgress(getValue(IModule::BYTES_SENT), true);
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 60));
    progressBar.draw(disp.getWindow());

    Display::TextBox bytesReceivedTextBox(sf::Vector2f(20, 20), "Bytes Received", disp.getFont());
    bytesReceivedTextBox.setPosition(vecCalc(container.getPosition(), 20, 120));
    bytesReceivedTextBox.draw(disp.getWindow());
    progressBar.setProgress(getValue(IModule::BYTES_RECEIVED), true);
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 160));
    progressBar.draw(disp.getWindow());

    Display::TextBox packetsSentTextBox(sf::Vector2f(20, 20), "Packets Sent", disp.getFont());
    packetsSentTextBox.setPosition(vecCalc(container.getPosition(), 20, 220));
    packetsSentTextBox.draw(disp.getWindow());
    progressBar.setProgress(getValue(IModule::PACKETS_SENT), true);
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 260));
    progressBar.draw(disp.getWindow());

    Display::TextBox packetsReceivedTextBox(sf::Vector2f(20, 20), "Packets Received", disp.getFont());
    packetsReceivedTextBox.setPosition(vecCalc(container.getPosition(), 20, 320));
    packetsReceivedTextBox.draw(disp.getWindow());
    progressBar.setProgress(getValue(IModule::PACKETS_RECEIVED), true);
    progressBar.setPosition(vecCalc(container.getPosition(), 20, 360));
    progressBar.draw(disp.getWindow());
}
