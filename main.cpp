#include "game.h"
#include "test.h"

using namespace sf;

int main() {
    int number = 0;
    //cout << "Run tests? (1 - Yes, 0 - No)" ;
    //cin >> number;
    if (number == 1) {
        gtest_main();
        return 0;
    }
    RenderWindow window(VideoMode(1280, 720), "Game");
    Event event;
    Game game;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (Keyboard::isKeyPressed(Keyboard::Escape)){
                event.type = Event::Closed;
            }
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        game.update_view(window);

        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
            game.update_player(1);
        } else if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
            game.update_player(2);
        } else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
            game.update_player(3);
        } else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
            game.update_player(4);
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            game.bullet.set_up(window, game.player.position.x, game.player.position.y);
        }
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            game.pick_up_weapon();
        }
        if (Keyboard::isKeyPressed(Keyboard::G)){
            game.drop_weapon();
        }
        game.update();
        game.draw(window);

    }

    return 0;
}