#include "game.h"

Game::Game() : view(), map() {
    level = 1;
    unit_amount = 0;
    item_amount = 0;
}

void Game::update_view(RenderWindow &window) {
    window.clear();

    view.setCenter(map.player.position.x + 8, map.player.position.y + 8);
    view.setSize(320, 180);
    window.setView(view);
}

void Game::update() {
    map.update_enemy();
    map.update_bullet();
}

void Game::draw(RenderWindow &window) {
    map.draw(window);
    map.player.draw(window);
    for (int i = 0; i < 4; i++){
        map.shooters[i].draw(window);
    }
    map.bullet.draw(window);
    window.display();
}

