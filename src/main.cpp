#include "Game.hpp"
#include "entities/Simple.hpp"

int main() {

    Game* game = new Game();

    // For testing we are going to append a simple entity to the game
    Simple* simple = new Simple();
    game->addEntity(simple);

    // We give the player a dummy item
    game->getPlayer()->getInventory()->addItem(new Item("dummy", "Dummy item", "Item created for testing purposes", "assets/dummy.png"));

    while(!game->shouldClose()) {

        game->update();
        game->render();

    }

}