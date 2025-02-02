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

void Krell::NCursesDisplay::drawDiskInfo(int maxX)
{
    const auto& diskInfo = dynamic_cast<const Modules::Disk&>(*_modules.at("disk"));
    std::stringstream totalDisk, usedDisk, freeDisk;

    drawBox(33, 1, 4, maxX - 3, "Disk Information");

    formatBytes(totalDisk, diskInfo.getValue(Krell::IModule::TOTAL));
    formatBytes(usedDisk, diskInfo.getValue(Krell::IModule::USED));
    formatBytes(freeDisk, diskInfo.getValue(Krell::IModule::FREE));

    mvprintw(34, 3, "Disk Usage:");
    drawProgressBar(35, 3, diskInfo.getValue(Krell::IModule::USEDPERCENT), maxX - 13);
    mvprintw(36, 3, "Total: %s Used: %s Free: %s", totalDisk.str().c_str(), usedDisk.str().c_str(), freeDisk.str().c_str());
}

void Krell::NCursesDisplay::drawNetworkInfo(int maxX)
{
    const auto& netInfo = dynamic_cast<const Modules::Network&>(*_modules.at("network"));
    drawBox(38, 1, 6, maxX - 3, "Network Information");

    bool isUp = netInfo.getValue(Krell::IModule::UP) > 0.5;
    attron(COLOR_PAIR(isUp ? 1 : 5) | A_BOLD);
    mvprintw(39, 3, "Status: %s", isUp ? "CONNECTED" : "DISCONNECTED");
    attroff(COLOR_PAIR(isUp ? 1 : 5) | A_BOLD);

    std::stringstream bytesSent, bytesReceived;
    formatBytes(bytesSent, netInfo.getValue(Krell::IModule::BYTES_SENT));
    formatBytes(bytesReceived, netInfo.getValue(Krell::IModule::BYTES_RECEIVED));

    int center = maxX / 2;
    int offset = center / 3;
    int leftCol = center - offset;
    int rightCol = center + offset;

    attron(COLOR_PAIR(2));
    mvprintw(40, leftCol - 10, "v Download");
    attroff(COLOR_PAIR(2));
    mvprintw(41, leftCol - 10, "Bytes: %s", bytesReceived.str().c_str());
    mvprintw(42, leftCol - 10, "Packets: %.0f", netInfo.getValue(Krell::IModule::PACKETS_RECEIVED));

    for (int i = 40; i <= 42; i++) {
        mvaddch(i, center, ACS_VLINE);
    }

    attron(COLOR_PAIR(4));
    mvprintw(40, rightCol - 4, "^ Upload");
    attroff(COLOR_PAIR(4));
    mvprintw(41, rightCol - 4, "Bytes: %s", bytesSent.str().c_str());
    mvprintw(42, rightCol - 4, "Packets: %.0f", netInfo.getValue(Krell::IModule::PACKETS_SENT));
}