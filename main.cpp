
#include <SFML/Graphics.hpp>
#include "unit.h"
#include "map.h"
#include "game.h"


using namespace sf;

int main() {
    RenderWindow window(VideoMode(1280, 720), "Leha");
    Event event;
    View view;


    Unit player;
    Map map;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();

        view.setCenter(player.position.x + 8, player.position.y + 8);
        view.setSize(320, 180);
        window.setView(view);

        map.draw(window);


        player.update(window, map);

        player.draw(window);
        window.display();

    }
    return 0;
}