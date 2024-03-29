#include "Player.hpp"

void Player::update(Game* game) {

    raylib::Vector2 movement_vector = {0, 0};
    movement_vector.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    movement_vector.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    movement_vector = movement_vector.Normalize();

    velocity.x = movement_vector.x * this->movementSpeed;
    velocity.y = movement_vector.y * this->movementSpeed;

    if (IsKeyPressed (KEY_E) ) { // TODO: Add keymap

        game->addEntity(&this->inventoryEntity);

    }

    if (IsKeyReleased(KEY_E)) {

        game->removeEntity(&this->inventoryEntity);

    }

    this->inventoryEntity.setPosition(this->position + Vector2{0, 32});

    mouse_position = game->getMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

        // Get the hovered entity
        std::vector<Entity*> entities_at_position = game->getEntitiesAtMousePosition();

        double damage = 10.0; // TODO: Calculate damage based on selected item.

        for (Entity* entity : entities_at_position) {

            entity->damage(damage);

        }

    }

    // TODO: Add a way to drop items.

}

void Player::render() {

    // Draw a rectangle at the players position
    this->getBoundingBox().Draw(RED); // TODO: Draw a player rights.

    // If the player has a held item
    if (this->isHoldingItem()) {

        // Draw the held item
        this->getHeldItem().render(mouse_position.x, mouse_position.y, 16, 16);

    }

}

Player::Player()
{
    inventory = Inventory(8, 1);
    health = 100;
    size = Vector2{32, 32};
    frozen = false;
    z_index = 2;
    inventoryEntity = InventoryEntity(Vector2{0, 0}, inventory);
}