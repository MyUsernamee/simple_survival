#include "Dummy.hpp"

void Dummy::render()
{

    this->getBoundingBox().Draw(RED);

}

Dummy::Dummy(raylib::Vector2 position, raylib::Vector2 size)
{

    this->position = position;
    this->size = size;
    this->frozen = false;

}

void Dummy::update(Game *game)
{

    // Do nothing

}