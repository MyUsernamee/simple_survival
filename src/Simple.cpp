#include "entities/Simple.hpp"

#include "Game.hpp"

void Simple::update(Game *game)
{

    physics_update(game);

}

void Simple::render()
{

    DrawRectangle(position.x, position.y, 50, 50, RED);

}