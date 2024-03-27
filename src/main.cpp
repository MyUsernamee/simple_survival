#include "Game.hpp"
#include "Player.hpp"
#include <Dummy.hpp>
#include "InventoryEntity.hpp"

int main() {

    Game* game = new Game();

    Dummy dummy = Dummy(raylib::Vector2(0, 0), raylib::Vector2(50, 50));
    game->addEntity(&dummy);

    // Give the player a test item
    Item item = Item("test", "Test Item", "", "assets/dummy.png");
    game->getPlayer()->getInventory()->addItem(item); // TODO: Add better api please
    game->getPlayer()->getInventory()->getSlot(0).setCount(64);

    // For testing we make a InventoryEntity
    Inventory inventory = Inventory(8, 8);
    InventoryEntity* inventoryEntity = new InventoryEntity(raylib::Vector2(0, 0), inventory);
    game->addEntity(inventoryEntity);

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