#pragma once

#include "Entity.hpp"

class DroppedItem : public Entity {

    public:

        DroppedItem(Item* item, raylib::Vector3 position, raylib::Vector3 velocity);

        void update(Game* game);
        void render();

    private:

        Item* item;
        raylib::Vector3 position;
        raylib::Vector3 velocity;

};