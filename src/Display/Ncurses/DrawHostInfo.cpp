/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawHostInfo
** File description:
** DrawHostInfo
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

#include <sstream>
#include <iomanip>

void Krell::NCursesDisplay::drawHostInfo(int maxX)
{
    const auto& hostInfo = dynamic_cast<const Modules::HostInfo&>(*_modules.at("host"));
    int boxWidth = maxX / 2;
    int startX = (maxX - boxWidth) / 2;

    std::string hostname = hostInfo.getHostname();
    std::string username = hostInfo.getUsername();
    drawBox(5, startX, 3, boxWidth, "System Information");
    int hostnameStart = startX + (boxWidth - hostname.length()) / 2;
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(6, hostnameStart, "%s", hostname.c_str());
    attroff(COLOR_PAIR(2) | A_BOLD);

    std::string userInfo = "User: " + username;
    int userStart = startX + (boxWidth - userInfo.length()) / 2;
    attron(COLOR_PAIR(3));
    mvprintw(7, userStart, "%s", userInfo.c_str());
    attroff(COLOR_PAIR(3));
}
