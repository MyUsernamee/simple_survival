#include "Entity.hpp"
#include "Game.hpp"

#include <raylib-cpp.hpp>

Entity::Entity()
{

    position =  raylib::Vector2{0, 0}; 
    velocity =  raylib::Vector2{0, 0};
    health = 0;
    frozen = false;
    z_index = 0;
    collisionBitMask = 0b11111111;

}

void Entity::physics_update(Game *game)
{

    position.x += velocity.x * game->getDeltaTime();
    position.y += velocity.y * game->getDeltaTime();

    // Apply friction
    velocity *= 0.8; // TODO: Make this a variable

}

bool Entity::collidesWith(Entity *entity)
{

    raylib::Rectangle rect1 = this->getBoundingBox();
    raylib::Rectangle rect2 = entity->getBoundingBox();

    if (rect1.CheckCollision(rect2) && canCollideWith(entity))
    {

        return true;

    }

    return false;

}

bool Entity::doCollision(Entity *entity)
{

    if (this->frozen) {

        return false;

    }

    if (collidesWith(entity))
    {

        raylib::Rectangle rect1 = this->getBoundingBox();
        raylib::Rectangle rect2 = entity->getBoundingBox();

        // Get the intersection as a rectangle
        raylib::Rectangle intersection = GetCollisionRec(rect1, rect2);

        // We get the resolution vector by finding the min of the intersections width and height
        raylib::Vector2 resolution = {intersection.width, intersection.height};

        if (resolution.x < resolution.y)
        {

            resolution.y = 0;

        }
        else
        {

            resolution.x = 0;

        }
        raylib::Vector2 direction = resolution.Normalize();

        // We move ourself and the other entity by half the resolution
        if (entity->isFrozen()) {

            // Only move ourselveds by the resolution
            position += resolution;

            // Cancel out the velocity in that direction
            if (resolution.x != 0) {

                velocity.x = 0;

            }
            else {

                velocity.y = 0;

            }

        }
        else {

            position += resolution / 2.0;
            entity->setPosition(entity->getPosition() - resolution / 2.0);

            // Cancel out the velocity in that direction
            raylib::Vector2 final_velocity = velocity + entity->getVelocity();
            final_velocity /= 2.0;
            final_velocity *= direction;
            velocity = final_velocity;
            entity->setVelocity(final_velocity);

        }

    }

    return false;

}
