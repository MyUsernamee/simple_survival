#pragma once

#include "Entity.hpp"

class DroppedItem : public Entity {

    public:

        DroppedItem(Slot item, raylib::Vector3 position, raylib::Vector3 velocity);

        void update(Game* game);
        void render();

    private:

        Slot item;
        raylib::Vector3 position;
        raylib::Vector3 velocity;

};