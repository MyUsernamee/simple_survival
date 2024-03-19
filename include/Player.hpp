
#pragma once

#include "Item.hpp"
#include "Slot.hpp"
#include "Inventory.hpp"

#include "raylib-cpp.hpp"
#include <array>

const int SLOT_COUNT = 10;

#include "Game.hpp"

class Game; // Forward declaration

class Player {

    // TODO: Should the player be an entity? Not too sure about this one.
    // I mean it makes sense, but at the same time the player is a special entity.
    // ?? Maybe will make entity later. 

    public:

        Player();

        void update(Game* game);
        void render(Game* game); // TODO: Render sprite, health, inventory, etc.

        raylib::Vector3 getPosition() { return position; }
        raylib::Vector3 getVelocity() { return velocity; }
        raylib::Vector2 getPosition2D() { return raylib::Vector2(position.x, position.y + position.z); } // Returns the position of the player in 2D space

        Inventory* getInventory() { return &inventory; }

        

    private:

        raylib::Vector3 position;
        raylib::Vector3 velocity;
        Inventory inventory;
        Slot heldItem;
        char health;
        bool holding_item;

};