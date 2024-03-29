#include "game.h"
#include "test.h"

using namespace sf;

int main() {
    gtest_main();

    srand(time(NULL));

    RenderWindow window(VideoMode(1280, 720), "Game");
    Event event;
    Game game;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
                window.close();
            }
        }
        game.update_view(window);

        if (Keyboard::isKeyPressed(Keyboard::A)) {
            game.update_player(1);
        } else if (Keyboard::isKeyPressed(Keyboard::W)) {
            game.update_player(2);
        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
            game.update_player(3);
        } else if (Keyboard::isKeyPressed(Keyboard::S)) {
            game.update_player(4);
        }
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            game.pick_up_weapon();
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            game.player_attack(window);
        }
        if (Keyboard::isKeyPressed(Keyboard::G)) {
            game.drop_weapon();
        }
        if (game.check == 2) {
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                game.restart();
            }
        }
        game.update();
        game.draw(window);
    }
    return 0;
}
