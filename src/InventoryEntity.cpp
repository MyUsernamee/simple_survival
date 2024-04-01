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
    this->size = raylib::Vector2{static_cast<float>(inventory.getWidth() * 16), static_cast<float>(inventory.getHeight() * 16)};
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

    // Right click takes half of the stack
    if (button == MOUSE_BUTTON_RIGHT && !player->isHoldingItem()) {

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
                this->inventory.getSlot(inventory_position.x, inventory_position.y).setCount(this->inventory.getSlot(inventory_position.x, inventory_position.y).getCount() / 2);

                // Set the count of the item to half + 1 if the count is odd
                player->getHeldItem().setCount(player->getHeldItem().getCount() / 2 + player->getHeldItem().getCount() % 2);

                // If the count is 0, remove the item from the player
                if (player->getHeldItem().getCount() == 0) {

                    player->getHeldItem().setItem(std::nullopt);

                }

            }

        }

    }

}

void InventoryEntity::onMouseReleased(Game *game, MouseButton button)
{

    Player* player = game->getPlayer();

    if (player->isHoldingItem()) {

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
            else if (item.has_value() && item.value().getId() == player->getHeldItem().getItem().value().getId() && this->inventory.getSlot(inventory_position.x, inventory_position.y).getCount() < 64) {
                // TODO: Make dry and clean code here.
                // Add as many items as possible to the inventory until the slot is full
                int count_to_add = std::min(player->getHeldItem().getCount(), 64 - this->inventory.getSlot(inventory_position.x, inventory_position.y).getCount());
                this->inventory.getSlot(inventory_position.x, inventory_position.y).add(count_to_add);

                // Remove the count from the slot
                if(!player->getHeldItem().remove(count_to_add)) {

                    // If the player's item is empty, remove the item from the player
                    player->getHeldItem().setItem(std::nullopt);

                }

            }

        }

    }

}