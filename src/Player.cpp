#include "Player.hpp"

void Player::update(Game* game) {

    // Update side to side velocity
    velocity.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    velocity.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);


    // TODO: Replace with player speed.
    velocity.x *= 3;
    velocity.y *= 3;

    if (position.z == 0.0 && IsKeyDown(KEY_SPACE)) {

        // Gravity TODO: Replace with player jump height
        velocity.z = -3;

    }

    // Update position
    position.x += velocity.x;
    position.y += velocity.y;
    position.z += velocity.z;

    velocity.z += 0.4;

    // Collision detection
    if (position.z > 0.0) {

        position.z = 0.0;
        velocity.z = 0.0;

    }

}

void Player::render(Game* game)
{

    DrawRectangle(position.x - 20,
        position.y + position.z - 20,
        40,
        40,
        raylib::Color(255, 0, 0, 255)); // TODO: Replace with sprite and add animation

    if (IsKeyDown(KEY_E)) { // TODO: REPLACE WITH KEYMAP

        // Draw inventory
        inventory.render(position.x - 16 * 4, position.y + 50, 16, 16); // TODO: Make pretty :) Replace 16 * 4 with width of inventory

        bool mouse_on_inventory = game->getMousePosition().x > position.x - 16 * 4 && game->getMousePosition().x < position.x + 16 * 4 &&
            game->getMousePosition().y > position.y + 50 && game->getMousePosition().y < position.y + 50 + 16;

        SetMouseCursor(mouse_on_inventory ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_ARROW);

        // Selected item
        int selected = (game->getMousePosition().x - position.x + 16 * 4) / 16; // TODO: This is Not dry. Replace with a function to get selected slot and if the player is hovering over inventory
        //DrawText(std::to_string(selected), position.x - 16 * 4, position.y + 50, 20, raylib::Color(255, 255, 255, 255));

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && mouse_on_inventory) {

            Slot& slot = inventory.getSlot(selected);

            if (slot.hasItem()) {

                heldItem.setItem(slot.getItem());
                heldItem.setCount(slot.getCount());

                slot.setItem(std::nullopt);
                slot.setCount(0);



            }

        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && heldItem.hasItem() && mouse_on_inventory) {

            Slot& slot = inventory.getSlot(selected);

            if (slot.hasItem()) {

                if (slot.getItem().value().getId() == heldItem.getItem().value().getId()) {

                    slot.add(heldItem.getCount());
                    heldItem.setItem(std::nullopt);
                    heldItem.setCount(0);

                }

            }
            else {

                slot.setItem(heldItem.getItem());
                slot.setCount(heldItem.getCount());
                heldItem.setItem(std::nullopt);
                heldItem.setCount(0);

            }

        }


    }
    else {

        SetMouseCursor(MOUSE_CURSOR_ARROW);

    }

    if (heldItem.hasItem()) {

        Texture2D item_texture = heldItem.getItem().value().getTexture();
        DrawTextureEx(item_texture, { static_cast<float>(game->getMousePosition().x), static_cast<float>(game->getMousePosition().y) }, 0, 1, WHITE);

    }

}

Player::Player()
{
    inventory = Inventory(8, 1);
    position = raylib::Vector3(0, 0, 0);
    velocity = raylib::Vector3(0, 0, 0);
    health = 100;
}