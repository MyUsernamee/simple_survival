#include "Game.hpp"
#include "Player.hpp"
#include <Dummy.hpp>
#include "InventoryEntity.hpp"
#include <Zombie.hpp>
#include <Mineable.hpp>

#include <iostream>
#include <filesystem>

int main() {

    // Print the working directory
    TraceLog(LOG_INFO, "Working Directory: %s", std::filesystem::current_path().c_str());

    Game* game = new Game();

    // Give the player a test item
    Item item = Item("test", "Test Item", "", "assets/dummy.png");
    game->getPlayer()->getInventory()->addItem(item); // TODO: Add better api please
    game->getPlayer()->getInventory()->getSlot(0).setCount(64);

    // For testing we make a InventoryEntity
    Inventory inventory = Inventory(8, 8);
    InventoryEntity* inventoryEntity = new InventoryEntity(raylib::Vector2(0, 0), inventory);
    game->addEntity(inventoryEntity);

    // Add a zombie to the game
    // Zombie* zombie = new Zombie(raylib::Vector2(0, 0));
    // game->addEntity(zombie);

    // We add a Mineable item to the game
    Mineable* mineable = new Mineable(100, 0, 100, "assets/dummy.png", item, 64);
    game->addEntity(mineable);

    // Give the dummy a werid bitmask
    //dummy.setCollisionBitMask(0b00000001);
    //game->getPlayer()->setCollisionBitMask(0b00000010);

    // For testing we are going to append a simple entity to the game
    // Simple* simple = new Simple();
    // game->addEntity(simple);

    while(!game->shouldClose()) {

        game->render();
        game->update();

    }

}