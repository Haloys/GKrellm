/*
** EPITECH PROJECT, 2025
** src/Modules/HostInfo
** File description:
** HostInfo
*/

#include <limits.h>
#include <pwd.h>

#include "Modules/HostInfo.hpp"
#include "Modules/CpuUsage.hpp"
#include "Display/SFML/Container.hpp"
#include "Display/SFML/ProgressBar.hpp"
#include "Display/SFML/TextBox.hpp"
#include "Display/SFML/Chart.hpp"
#include "IModule.hpp"
#include "Utils.hpp"

Krell::Modules::HostInfo::HostInfo() : IModule(sf::Vector2f(400, 190), "HostInfo")
{
    refresh();
}

void Krell::Modules::HostInfo::refreshHostname()
{
    char hostname[HOST_NAME_MAX];

    if (gethostname(hostname, HOST_NAME_MAX) == 0) {
        _hostname = hostname;
    } else {
        _hostname = "unknown";
    }
}

void Krell::Modules::HostInfo::refreshUsername()
{
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if (pw) {
        _username = pw->pw_name;
    } else {
        _username = "unknown";
    }
}

void Krell::Modules::HostInfo::refresh()
{
    refreshHostname();
    refreshUsername();
}

double Krell::Modules::HostInfo::getValue(ModuleKey key) const
{
    (void)key;
    return 0.0;
}

void Krell::Modules::HostInfo::drawModule(SFMLDisplay &disp)
{
    Display::Container container(sf::Vector2f(950, 380), size);
    container.draw(disp.getWindow());

    Display::TextBox titleBox(sf::Vector2f(360, 30), "Host Information", disp.getFont());
    titleBox.setPosition(vecCalc(container.getPosition(), 20, 20));
    titleBox.draw(disp.getWindow());

    std::string hostInfo = "Hostname: " + _hostname + "\n";
    hostInfo += "Username: " + _username + "\n";

    Display::TextBox infoBox(sf::Vector2f(360, 60), hostInfo, disp.getFont());
    infoBox.setPosition(vecCalc(container.getPosition(), 20, 70));
    infoBox.draw(disp.getWindow());
}
