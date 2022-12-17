#include "test.h"
#include "game.h"

TEST(Unit, constructor) {
    Unit unit;
    EXPECT_EQ(unit.dead, 0);
    EXPECT_EQ(unit.hp, 100);
    EXPECT_EQ(unit.position.x, 0);
    EXPECT_EQ(unit.position.y, 0);
    EXPECT_DOUBLE_EQ(unit.speed, 0.2);
}

TEST(Unit, moving) {
    Unit unit;
    unit.set_position(40,50);
    EXPECT_EQ(unit.position.x, 40);
    EXPECT_EQ(unit.position.y, 50);
    unit.move_x(30);
    unit.move_y(50);
    EXPECT_DOUBLE_EQ(unit.position.x, 70);
    EXPECT_DOUBLE_EQ(unit.position.y, 100);
    unit.move_x(-23.123);
    unit.move_y(-40.31);
    EXPECT_DOUBLE_EQ(unit.position.x, 46.876998901367188);
    EXPECT_DOUBLE_EQ(unit.position.y, 59.689998626708984);
}

TEST(Unit, get_damage) {
    Unit unit;
    unit.get_damage(33);
    EXPECT_EQ(unit.hp, 67);
}

TEST(Bullet, constructor) {
    Bullet bullet;
    EXPECT_EQ(bullet.speed, 0.8);
    EXPECT_EQ(bullet.check, 0);
    EXPECT_EQ(bullet.damage, 33);
}

TEST(Bullet, moving) {
    Bullet bullet;
    bullet.move_x(10);
    bullet.move_y(50.4);
    EXPECT_EQ(bullet.position.x, 10);
    EXPECT_DOUBLE_EQ(bullet.position.y, 50.400001525878906);
    bullet.move_x(-10.3);
    bullet.move_y(-90);
    EXPECT_DOUBLE_EQ(bullet.position.x, -0.30000001192092896);
    EXPECT_DOUBLE_EQ(bullet.position.y, -39.599998474121094);
}

TEST(Game, moving) {
    Game game;
    EXPECT_EQ(game.player.position.x, 192);
    EXPECT_EQ(game.player.position.y, 128);
    //вправо
    for (int i = 0; i < 100; i++){
        game.update_player(3);
    }
    EXPECT_DOUBLE_EQ(game.player.position.x, 211.99969482421875);
    EXPECT_DOUBLE_EQ(game.player.position.y, 128);
    //влево
    for (int i = 0; i < 100; i++){
        game.update_player(1);
    }
    EXPECT_DOUBLE_EQ(game.player.position.x, 192);
    EXPECT_DOUBLE_EQ(game.player.position.y, 128);
    //наверх
    for (int i = 0; i < 100; i++){
        game.update_player(2);
    }
    EXPECT_DOUBLE_EQ(game.player.position.x, 192);
    EXPECT_DOUBLE_EQ(game.player.position.y, 108.00030517578125);
    //вниз
    for (int i = 0; i < 100; i++){
        game.update_player(4);
    }
    EXPECT_DOUBLE_EQ(game.player.position.x, 192);
    EXPECT_DOUBLE_EQ(game.player.position.y, 128);
}

TEST(Game, take_damage){
    Game game;
    game.update();
    EXPECT_EQ(game.player.hp, 100);
    for (int i = 0; i < 40; i++){
        game.enemies_attack();
        game.update();
    }
    EXPECT_EQ(game.player.hp, 67);
}

TEST(Game, shooting) {
    Game game;
    game.update();
    EXPECT_EQ(game.player.weapon, nullptr);
    game.weapons.push_back(make_shared<ak47>());
    game.player.set_weapon(game.weapons[game.weapons.size() - 1]);
    EXPECT_EQ(game.player.weapon->check, 1);
    EXPECT_EQ(game.player.weapon->shot, false);
    RenderWindow window(VideoMode(1280, 720), "Game");
    game.player_attack(window);
    EXPECT_EQ(game.player.weapon->shot, true);

}

TEST(Game, check_game) {
    Game game;
    game.update();

    //check = 0 - игра в процессе
    //check = 1 - игрок умер
    //check = 2 - игрок победил

    //игра только началась
    EXPECT_EQ(game.check, 0);
    game.player.get_damage(100);
    //игрок умер
    game.check_game();
    EXPECT_EQ(game.check, 1);
    //игра перезапустилась
    game.restart();
    EXPECT_EQ(game.check, 0);
    int j = game.enemies.size();
    for (int i = 0; i < j; i++){
        game.enemies[game.enemies.size() - 1]->get_damage(100);
        game.update_enemies();
    }
    //все противники мертвы
    game.check_game();
    EXPECT_EQ(game.check, 2);
}

int gtest_main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}