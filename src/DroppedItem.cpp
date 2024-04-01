#include "DroppedItem.hpp"

#include "Game.hpp"
#include "Player.hpp"

DroppedItem::DroppedItem(int x, int y, Item item)
{

    this->setPosition(raylib::Vector2{static_cast<float>(x), static_cast<float>(y)});
    this->item = item;

    this->size = raylib::Vector2{static_cast<float>(this->item.getTexture().width), static_cast<float>(this->item.getTexture().height)};
    

}

void DroppedItem::update(Game *game)
{

    // Do nothing

}

void DroppedItem::render()
{

    DrawTextureEx(item.getTexture(), raylib::Vector2{position.x - size.x / 2, position.y - size.y / 2}, 0, 1, WHITE);

}

void DroppedItem::onCollision(Game* game, Entity *entity)
{

    if (entity == game->getPlayer())
    {

        // Add the item to the player's inventory
        game->getPlayer()->getInventory()->addItem(item);

        // Remove the entity from the game
        game->removeEntity(this);

    }

}