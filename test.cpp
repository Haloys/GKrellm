#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>

using namespace sf;

int main(void)
{
    Window win(VideoMode(1920, 1080), "test");
    Event e;

    while (win.isOpen()) {
        win.display();
        while (win.pollEvent(e))
            continue;
        if (e.type == sf::Event::Closed)
            break;
    }
    win.close();
}
