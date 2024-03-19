#include "Game.hpp"
#include "entities/Simple.hpp"

int main() {

    Game* game = new Game();

    // For testing we are going to append a simple entity to the game
    Simple* simple = new Simple();
    game->addEntity(simple);

    while(!game->shouldClose()) {

        game->update();
        game->render();

    }

}