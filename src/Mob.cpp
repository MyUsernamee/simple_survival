#include "Mob.hpp"

Mob::Mob(raylib::Vector2 position, raylib::Vector2 size, double speed)
{

    this->position = position;
    this->size = size;
    this->speed = speed;
    this->movement = raylib::Vector2(0, 0);

}

void Mob::update(Game *game)
{

    if (!this->frozen)
    {
        this->update_movement(game);
        this->position += this->movement * this->speed;
    }

}

void Mob::render()
{

    this->getBoundingBox().Draw(RED);

}

