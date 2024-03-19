#include "Entity.hpp"

#include <raylib-cpp.hpp>

Entity::Entity()
{

    position =  raylib::Vector3{0, 0, 0}; 
    velocity =  raylib::Vector3{0, 0, 0};

}

Entity::Entity(raylib::Vector3 position, raylib::Vector3 velocity)
{

    this->position = position;
    this->velocity = velocity;

}

void Entity::physics_update(Game *game)
{

    position.x += velocity.x * game->getDeltaTime();
    position.y += velocity.y * game->getDeltaTime();
    position.z += velocity.z * game->getDeltaTime();

}