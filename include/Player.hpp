
#pragma once

#include "Item.hpp"
#include "Slot.hpp"
#include "Inventory.hpp"
#include "Entity.hpp"

#include "raylib-cpp.hpp"
#include <array>


const int SLOT_COUNT = 10;

#include "Game.hpp"

class Game; // Forward declaration

#include "Entity.hpp"

class Player: public Entity {

    // TODO: Should the player be an entity? Not too sure about this one.
    // I mean it makes sense, but at the same time the player is a special entity.
    // ?? Maybe will make entity later. 

    public:

        Player();

        void update(Game* game);
        void render(); // TODO: Render sprite, health, inventory, etc.

        Inventory* getInventory() { return &inventory; }

        Slot& getHeldItem() { return heldItem; }
        void setHeldItem(Slot heldItem) { this->heldItem = heldItem; }        

        bool isHoldingItem() { return heldItem.hasItem(); }


    private:

        Inventory inventory;
        Slot heldItem;
        double movementSpeed = 100.0;
        //bool holding_item;

};