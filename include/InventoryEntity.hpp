#pragma once


#include "Entity.hpp"
#include "Inventory.hpp"


class InventoryEntity : public Entity {

    public:

        InventoryEntity();
        InventoryEntity(raylib::Vector2 position, Inventory& inventory);

        void update(Game* game);
        void render();

        Inventory* getInventory() { return &inventory; }

        void onMousePressed(Game* game, MouseButton button);
        void onMouseReleased(Game* game, MouseButton button);

    private:

        Inventory inventory;

};