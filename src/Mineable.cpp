#include "Mineable.hpp"
#include "Game.hpp"
#include <DroppedItem.hpp>


Mineable::Mineable(int x, int y, int health, const char * texture, Item dropped_item)
{

    // TODO: Implement this and the reset of this class
    this->setPosition(raylib::Vector2{x, y});
    this->setHealth(health);
    this->setTexture(texture);
    this->dropped_item = dropped_item;

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

    DroppedItem* dropped_item = new DroppedItem(position.x, position.y, this->dropped_item);
    game->addEntity(dropped_item);

    // Remove the entity from the game
    game->removeEntity(this);

}
