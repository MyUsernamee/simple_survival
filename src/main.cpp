#include "Game.hpp"
#include "Player.hpp"
#include <Dummy.hpp>

int main() {

    Game* game = new Game();

    Dummy dummy = Dummy(raylib::Vector2(0, 0), raylib::Vector2(50, 50));
    game->addEntity(&dummy);

    // Give the dummy a werid bitmask
    dummy.setCollisionBitMask(0b00000001);
    game->getPlayer()->setCollisionBitMask(0b00000010);

    // For testing we are going to append a simple entity to the game
    // Simple* simple = new Simple();
    // game->addEntity(simple);

    while(!game->shouldClose()) {

        game->render();
        game->update();

    }

}