
#pragma once

#include <raylib-cpp.hpp>
#include "Game.hpp"

class Game; // Forward declaration

class Entity {

    public:

        Entity();
        // TODO: REWRITE !!!! We need to find someway of implementing inheritance. While Composition would be nice it seemse a bit complicated.

        virtual void update(Game* game) = 0;
        virtual void render() = 0;

        raylib::Vector2 getPosition() { return position; }
        void setPosition(raylib::Vector2 position) { this->position = position; }

        raylib::Vector2 getSize() { return size; }
        void setSize(raylib::Vector2 size) { this->size = size; }

        int getHealth() { return health; }
        void setHealth(int health) { this->health = health; }

        char getCollisionBitMask() { return collisionBitMask; }

        char canCollideWith(Entity* entity) { return collisionBitMask & entity->getCollisionBitMask(); }
        char canCollideWith(char collisionBitMask) { return this->collisionBitMask & collisionBitMask; }

        void damage(int damage) { health -= damage; }

        int getZIndex() { return z_index; }
        void setZIndex(int z_index) { this->z_index = z_index; }

    protected:

        raylib::Vector2 position;
        raylib::Vector2 size; // Bounding Box.
        int health; // Health of the entity -1 means infinite health.
        char collisionBitMask;

        int z_index;


};