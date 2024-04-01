#include "Mineable.hpp"
#include "Game.hpp"
#include <DroppedItem.hpp>


Mineable::Mineable(int x, int y, int health, const char * texture, Item dropped_item, int amount)
{

    // TODO: Implement this and the reset of this class
    this->setPosition(raylib::Vector2{static_cast<float>(x), static_cast<float>(y)});
    this->setHealth(health);
    this->setTexture(texture);
    this->dropped_item = dropped_item;
    this->amount = amount;

    frozen = true;

    this->size = raylib::Vector2{static_cast<float>(this->texture.width) * MINEABLE_SCALE, static_cast<float>(this->texture.height) * MINEABLE_SCALE};


}

void Mineable::update(Game *game)
{

    // Do nothing

}

void Mineable::render()
{

    DrawTextureEx(texture, raylib::Vector2{position.x - size.x / 2, position.y - size.y / 2}, 0, MINEABLE_SCALE, WHITE);

}

void Mineable::onDeath(Game *game)
{

    for (int i = 0; i < amount; i++)
    {

        // Create a new DroppedItem entity
        DroppedItem* dropped_item = new DroppedItem(position.x, position.y, this->dropped_item);

        dropped_item->setVelocity(raylib::Vector2{GetRandomValue(-100.0, 100.0), GetRandomValue(-100.0, 100.0)});

        // TODO: BUG: It is possible to get more than the amount given, I am guessing this has to do with the fact that
        // We are removing the dropped item entity in the middle of the collision loop
        // So we will have to fix that but I want to work on the crafting system for now.

        // Add the entity to the game
        game->addEntity(dropped_item);

    }

    // Remove the entity from the game
    game->removeEntity(this);

}
