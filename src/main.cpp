/*
** EPITECH PROJECT, 2025
** Src/main
** File description:
** Main
*/

#include <memory>
#include <iostream>

#include "NCursesDisplay.hpp"
#include "SFMLDisplay.hpp"

static std::unique_ptr<Krell::IDisplay> createDisplay(const std::string& mode)
{
    if (mode == "ncurses")
        return std::make_unique<Krell::NCursesDisplay>();
    if (mode == "sfml")
        return std::make_unique<Krell::SFMLDisplay>();
    throw std::runtime_error("Invalid mode. Use 'ncurses' or 'sfml'");
}

static void run(Krell::IDisplay& display)
{
    display.start();
    while (display.isRunning()) {
        display.handleEvents();
        display.refresh();
    }
    display.stop();
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " [ncurses/sfml]" << std::endl;
        return 1;
    }
    try {
        auto display = createDisplay(av[1]);
        run(*display);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
