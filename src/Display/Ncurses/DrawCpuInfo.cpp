/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawCpuInfo
** File description:
** DrawCpuInfo
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

#include <sstream>
#include <iomanip>

void Krell::NCursesDisplay::drawCpuInfo(int maxX)
{
    const auto& cpuInfo = dynamic_cast<const Modules::CpuInfo&>(*_modules.at("cpu_info"));

    drawBox(10, 1, 7, maxX - 3, "CPU Information");

    mvprintw(11, 3, "Model: %s", cpuInfo.ModelName().c_str());
    mvprintw(12, 3, "Cores: %zu (Threads: %zu)", cpuInfo.CpuCores(), cpuInfo.CpuThreads());
    mvprintw(13, 3, "Frequency: %zu MHz", cpuInfo.CpuMhz());
    mvprintw(14, 3, "Cache: %s", cpuInfo.CacheSize().c_str());
    mvprintw(15, 3, "Vendor: %s", cpuInfo.VendorId().c_str());
}

void Krell::NCursesDisplay::drawCpuUsage(int maxX)
{
    const auto& cpuUsage = dynamic_cast<const Modules::CpuUsage&>(*_modules.at("cpu_usage"));

    drawBox(18, 1, 5, maxX - 3, "CPU Usage");

    mvprintw(19, 3, "Current CPU Usage:");
    drawProgressBar(20, 3, cpuUsage.getValue(Krell::IModule::USEDPERCENT), maxX - 13);
    mvprintw(21, 3, "Free: %.1f%%", cpuUsage.getValue(Krell::IModule::FREEPERCENT));
}

void formatMemory(std::stringstream& ss, size_t kb)
{
    if (kb > 1024 * 1024) {
        ss << std::fixed << std::setprecision(2) << (kb / (1024.0 * 1024.0)) << " GB";
    } else if (kb > 1024) {
        ss << std::fixed << std::setprecision(2) << (kb / 1024.0) << " MB";
    } else {
        ss << kb << " KB";
    }
}

void Krell::NCursesDisplay::drawMemoryInfo(int maxX)
{
    const auto& memInfo = dynamic_cast<const Modules::MemoryInfo&>(*_modules.at("mem"));
    std::stringstream totalMem, usedMem, availMem, swapTotal, swapUsed;

    drawBox(24, 1, 8, maxX - 3, "Memory Information");

    formatMemory(totalMem, memInfo.Total());
    formatMemory(usedMem, memInfo.Used());
    formatMemory(availMem, memInfo.Available());
    formatMemory(swapTotal, memInfo.SwapTotal());
    formatMemory(swapUsed, memInfo.SwapUsed());

    mvprintw(25, 3, "Memory Usage:");
    drawProgressBar(26, 3, memInfo.usePercentage(), maxX - 13);
    mvprintw(27, 3, "Total: %s Used: %s Available: %s", totalMem.str().c_str(), usedMem.str().c_str(), availMem.str().c_str());
    mvprintw(28, 3, "Swap Usage:");
    drawProgressBar(29, 3, memInfo.swapUsePercentage(), maxX - 13);
    mvprintw(30, 3, "Total: %s Used: %s", swapTotal.str().c_str(), swapUsed.str().c_str());
}
