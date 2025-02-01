/*
** EPITECH PROJECT, 2025
** src/Display/Ncurses/DrawInfo
** File description:
** DrawInfo
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

#include <sstream>
#include <iomanip>

void Krell::NCursesDisplay::drawCpuInfo(int maxX)
{
    const auto& cpuInfo = dynamic_cast<const Modules::CpuInfo&>(*_modules.at("cpu_info"));
    drawBox(1, 1, 7, maxX - 3, "CPU Information");
    mvprintw(2, 3, "Model: %s", cpuInfo.ModelName().c_str());
    mvprintw(3, 3, "Cores: %zu (Threads: %zu)", cpuInfo.CpuCores(), cpuInfo.CpuThreads());
    mvprintw(4, 3, "Frequency: %zu MHz", cpuInfo.CpuMhz());
    mvprintw(5, 3, "Cache: %s", cpuInfo.CacheSize().c_str());
    mvprintw(6, 3, "Vendor: %s", cpuInfo.VendorId().c_str());
}

void Krell::NCursesDisplay::drawCpuUsage(int maxX)
{
    const auto& cpuUsage = dynamic_cast<const Modules::CpuUsage&>(*_modules.at("cpu_usage"));
    drawBox(9, 1, 5, maxX - 3, "CPU Usage");
    mvprintw(10, 3, "Current CPU Usage:");
    drawProgressBar(11, 3, cpuUsage.getValue(Krell::IModule::USEDPERCENT), maxX - 13);
    mvprintw(12, 3, "Free: %.1f%%", cpuUsage.getValue(Krell::IModule::FREEPERCENT));
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
    drawBox(15, 1, 8, maxX - 3, "Memory Information");
    std::stringstream totalMem, usedMem, availMem, swapTotal, swapUsed;
    formatMemory(totalMem, memInfo.Total());
    formatMemory(usedMem, memInfo.Used());
    formatMemory(availMem, memInfo.Available());
    formatMemory(swapTotal, memInfo.SwapTotal());
    formatMemory(swapUsed, memInfo.SwapUsed());

    mvprintw(16, 3, "Memory Usage:");
    drawProgressBar(17, 3, memInfo.usePercentage(), maxX - 13);
    mvprintw(18, 3, "Total: %s  Used: %s  Available: %s",  totalMem.str().c_str(), usedMem.str().c_str(), availMem.str().c_str());
    mvprintw(19, 3, "Swap Usage:");
    drawProgressBar(20, 3, memInfo.swapUsePercentage(), maxX - 13);
    mvprintw(21, 3, "Total: %s  Used: %s", swapTotal.str().c_str(), swapUsed.str().c_str());
}
