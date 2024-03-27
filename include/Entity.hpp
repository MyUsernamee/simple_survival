
#pragma once

#include <raylib-cpp.hpp>

class Game; // Forward declaration

class Entity {

    public:

        Entity();
        // TODO: REWRITE !!!! We need to find someway of implementing inheritance. While Composition would be nice it seemse a bit complicated.

        virtual void update(Game* game) = 0;
        void physics_update(Game* game);
        bool doCollision(Entity* entity); // Returns true if the entity collided with another entity.

        virtual void render() = 0;

        raylib::Vector2 getPosition() { return position; }
        void setPosition(raylib::Vector2 position) { this->position = position; }

        raylib::Vector2 getVelocity() { return velocity; }
        void setVelocity(raylib::Vector2 velocity) { this->velocity = velocity; }

        raylib::Vector2 getSize() { return size; }
        void setSize(raylib::Vector2 size) { this->size = size; }

        int getHealth() { return health; }
        void setHealth(int health) { this->health = health; }

        char getCollisionBitMask() { return collisionBitMask; }
        void setCollisionBitMask(char collisionBitMask) { this->collisionBitMask = collisionBitMask; }
        bool collidesWith(Entity* entity);

        raylib::Rectangle getBoundingBox() const { return raylib::Rectangle{position.x - size.x / 2, position.y - size.y / 2, size.x, size.y}; }

        /**
         * @brief Checks if the entity can collide with another entity.
         * @return 0 if can't collide or the intersection of the bitmasks.
        */
        char canCollideWith(Entity* entity) { return collisionBitMask & entity->getCollisionBitMask(); }
        char canCollideWith(char collisionBitMask) { return this->collisionBitMask & collisionBitMask; }

        virtual void onCollision(Entity* entity) = 0; // Called when the entity collides with another entity.

        /**
         * @brief Damages the entity.
         * @param damage The amount of damage to deal to the entity.
        */
        void damage(int damage) { health -= damage; onDamage(damage); if (health <= 0)  onDeath(); }

        void onDamage(int damage) {};
        void onDeath() {}; // Called when the entity dies.

        /**
         * @brief Z-Index of the entity.
         * @return The z-index of the entity.
         * @note The z-index is used to determine the order in which entities are rendered.
        */
        int getZIndex() { return z_index; }
        void setZIndex(int z_index) { this->z_index = z_index; }

        bool isFrozen() { return frozen; }

        void onMouseOver(Game* game) {};
        virtual void onMousePressed(Game* game, MouseButton button) {};
        virtual void onMouseReleased(Game* game, MouseButton button) {};

        bool contains(raylib::Vector2 point) { return getBoundingBox().CheckCollision(point); }

    protected:

        raylib::Vector2 position;
        raylib::Vector2 velocity;
        raylib::Vector2 size; // Bounding Box.
        int health; // Health of the entity -1 means infinite health.
        char collisionBitMask;
        bool frozen;
        int z_index;


};