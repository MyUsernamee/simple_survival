
#pragma once

#include "Item.hpp"
#include "Slot.hpp"

#include "raylib-cpp.hpp"
#include <array>

const int SLOT_COUNT = 10;

class Player {

    public:

        Player();

        void update();
        void render();

        raylib::Vector3 getPosition() { return position; }
        raylib::Vector3 getVelocity() { return velocity; }
        raylib::Vector2 getPosition2D() { return raylib::Vector2(position.x, position.y + position.z); } // Returns the position of the player in 2D space

    private:

        raylib::Vector3 position;
        raylib::Vector3 velocity;
        std::array<Slot*, SLOT_COUNT> inventory; // TODO: Render ME
        char health;

};