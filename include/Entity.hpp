
#pragma once

#include <raylib-cpp.hpp>
#include "Game.hpp"

class Game; // Forward declaration

class Entity {

    public:

        Entity();
        Entity(raylib::Vector3 position, raylib::Vector3 velocity);

        void physics_update(Game* game);
        virtual void update(Game* game) = 0;
        virtual void render() = 0;

        raylib::Vector3 getPosition() { return position; }
        raylib::Vector3 getVelocity() { return velocity; }
        
        void setPosition(raylib::Vector3 position) { this->position = position; }
        void setVelocity(raylib::Vector3 velocity) { this->velocity = velocity; }

    protected:
    
            raylib::Vector3 position;
            raylib::Vector3 velocity;


};