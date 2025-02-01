/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawNetworkInfo
** File description:
** DrawNetworkInfo
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

#include <sstream>
#include <iomanip>

void formatBytes(std::stringstream& ss, double bytes)
{
    if (bytes > 1024 * 1024 * 1024) {
        ss << std::fixed << std::setprecision(2) << (bytes / (1024.0 * 1024.0 * 1024.0)) << " GB";
    } else if (bytes > 1024 * 1024) {
        ss << std::fixed << std::setprecision(2) << (bytes / (1024.0 * 1024.0)) << " MB";
    } else if (bytes > 1024) {
        ss << std::fixed << std::setprecision(2) << (bytes / 1024.0) << " KB";
    } else {
        ss << std::fixed << std::setprecision(0) << bytes << " B";
    }
}

void Krell::NCursesDisplay::drawNetworkInfo(int maxX)
{
    const auto& netInfo = dynamic_cast<const Modules::Network&>(*_modules.at("network"));
    drawBox(37, 1, 6, maxX - 3, "Network Information");

    bool isUp = netInfo.getValue(Krell::IModule::UP) > 0.5;
    attron(COLOR_PAIR(isUp ? 1 : 5) | A_BOLD);
    mvprintw(38, 3, "Status: %s", isUp ? "CONNECTED" : "DISCONNECTED");
    attroff(COLOR_PAIR(isUp ? 1 : 5) | A_BOLD);

    std::stringstream bytesSent, bytesReceived;
    formatBytes(bytesSent, netInfo.getValue(Krell::IModule::BYTES_SENT));
    formatBytes(bytesReceived, netInfo.getValue(Krell::IModule::BYTES_RECEIVED));

    attron(COLOR_PAIR(4));
    mvprintw(39, maxX - 40, "^ Upload");
    attroff(COLOR_PAIR(4));
    mvprintw(40, maxX - 40, "Bytes: %s", bytesSent.str().c_str());
    mvprintw(41, maxX - 40, "Packets: %.0f", netInfo.getValue(Krell::IModule::PACKETS_SENT));

    attron(COLOR_PAIR(2));
    mvprintw(39, 18, "v Download");
    attroff(COLOR_PAIR(2));
    mvprintw(40, 18, "Bytes: %s", bytesReceived.str().c_str());
    mvprintw(41, 18, "Packets: %.0f", netInfo.getValue(Krell::IModule::PACKETS_RECEIVED));

    for (int i = 39; i <= 41; i++) {
        mvaddch(i, maxX/2 - 2, ACS_VLINE);
    }
}