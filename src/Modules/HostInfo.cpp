/*
** EPITECH PROJECT, 2025
** src/Modules/HostInfo
** File description:
** HostInfo
*/

#include <limits.h>
#include <pwd.h>

#include "Modules/HostInfo.hpp"

Krell::Modules::HostInfo::HostInfo()
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
