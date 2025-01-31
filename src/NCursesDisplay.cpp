/*
** EPITECH PROJECT, 2025
** Src/NcursesDisplay
** File description:
** NcursesDisplay
*/

#include "NCursesDisplay.hpp"
#include "IModule.hpp"

Krell::NCursesDisplay::NCursesDisplay() : _isRunning(false), IDisplay()
{

}

Krell::NCursesDisplay::~NCursesDisplay()
{
    if (_isRunning) {
        stop();
    }
}

void Krell::NCursesDisplay::start()
{
    _window = initscr();
    noecho();
    cbreak();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    keypad(_window, TRUE);
    nodelay(_window, TRUE);
    timeout(0);
    _isRunning = true;
}

void Krell::NCursesDisplay::refresh()
{
    ::refresh();
}

void Krell::NCursesDisplay::stop()
{
    endwin();
    _isRunning = false;
}

void Krell::NCursesDisplay::handleEvents()
{
    int ch = getch();
    if (ch != ERR) {
        if (ch == 'q' || ch == 'Q') {
            _isRunning = false;
        }
    }
}

bool Krell::NCursesDisplay::isRunning() const
{
    return _isRunning;
}

void Krell::NCursesDisplay::drawModule(const IModule& module)
{
    clear();  // Nettoyer l'écran avant de dessiner

    // Afficher le titre
    attron(A_BOLD);
    mvprintw(1, 2, "CPU STATISTICS");
    attroff(A_BOLD);

    // Afficher l'utilisation CPU avec une barre de progression
    mvprintw(3, 2, "CPU Usage:");
    float usagePercent = static_cast<float>(module.getValue("usedPercent"));
    
    // Dessiner la barre de progression
    mvprintw(4, 2, "[");
    int barWidth = 50;
    int usedWidth = static_cast<int>((usagePercent / 100.0f) * barWidth);
    
    attron(COLOR_PAIR(1));  // Couleur verte pour la partie utilisée
    for (int i = 0; i < usedWidth; i++)
        printw("|");
    attroff(COLOR_PAIR(1));
    
    // Compléter la barre avec des espaces
    for (int i = usedWidth; i < barWidth; i++)
        printw(" ");
    
    printw("] %.1f%%", usagePercent);

    // Afficher les détails
    mvprintw(6, 2, "Used CPU: %.1f%%", usagePercent);
    mvprintw(7, 2, "Free CPU: %.1f%%", module.getValue("freePercent"));

    // Ligne de séparation
    mvprintw(9, 2, "----------------------------------------");

    // Position du curseur en bas
    move(LINES - 1, 0);

    // Instructions
    attron(A_DIM);
    mvprintw(LINES - 2, 2, "Press 'q' to quit");
    attroff(A_DIM);
}