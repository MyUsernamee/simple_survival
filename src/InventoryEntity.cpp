#include "InventoryEntity.hpp"
#include "Inventory.hpp"
#include "Player.hpp"

InventoryEntity::InventoryEntity()
{

    //frozen = true;
    

}

InventoryEntity::InventoryEntity(raylib::Vector2 position, Inventory &inventory)
{

    position = position;
    this->inventory = inventory;
    this->size = raylib::Vector2{inventory.getWidth() * 16, inventory.getHeight() * 16};
    this->collisionBitMask = 0;
    z_index = 1;
    frozen = true;

}

void InventoryEntity::update(Game *game)
{

    // Do nothing

}

void InventoryEntity::render()
{

    this->inventory.render(this->position.x - this->inventory.getWidth() * 8, this->position.y - this->inventory.getHeight() * 8, 16, 16);

}

void InventoryEntity::onMousePressed(Game *game, MouseButton button)
{

    Player* player = game->getPlayer();

    if (button == MOUSE_BUTTON_LEFT && !player->isHoldingItem()) {

        // Get the mouse_position relative to the inventory
        raylib::Vector2 mouse_position = game->getMousePosition() - this->position + this->size / 2;
        raylib::Vector2 inventory_position = raylib::Vector2{mouse_position.x / 16, mouse_position.y / 16};

        // Check if the inventory_position is within the bounds of the inventory
        if (inventory_position.x >= 0 && inventory_position.x < this->inventory.getWidth() && inventory_position.y >= 0 && inventory_position.y < this->inventory.getHeight()) {

            // Get the item at the inventory_position
            std::optional<Item> item = this->inventory.getItem(inventory_position.x, inventory_position.y);

            // If the item is not null
            if (item.has_value()) {

                // Pick up the item
                player->setHeldItem(this->inventory.getSlot(inventory_position.x, inventory_position.y));

                // Remove the item from the inventory
                this->inventory.getSlot(inventory_position.x, inventory_position.y).setItem(std::nullopt); // TODO: Make clear function

            }

        }



    }

}

void InventoryEntity::onMouseReleased(Game *game, MouseButton button)
{

    Player* player = game->getPlayer();

    if (button == MOUSE_BUTTON_LEFT && player->isHoldingItem()) {

        // Get the mouse_position relative to the inventory
        raylib::Vector2 mouse_position = game->getMousePosition() - this->position + this->size / 2;
        raylib::Vector2 inventory_position = raylib::Vector2{mouse_position.x / 16, mouse_position.y / 16};

        // Check if the inventory_position is within the bounds of the inventory
        if (inventory_position.x >= 0 && inventory_position.x < this->inventory.getWidth() && inventory_position.y >= 0 && inventory_position.y < this->inventory.getHeight()) {

            // Get the item at the inventory_position
            std::optional<Item> item = this->inventory.getItem(inventory_position.x, inventory_position.y);

            // If the item is null
            if (!item.has_value()) {

                // Place the item in the inventory
                this->inventory.setSlot(inventory_position.x, inventory_position.y, player->getHeldItem());

                // Remove the item from the player
                player->getHeldItem().setItem(std::nullopt);

            }

        }

    }

}