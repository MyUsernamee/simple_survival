#include "entities/DroppedItem.hpp"

void DroppedItem::update(Game *game)
{

    // We see if the player is close to the item
    Player* player = game->getPlayer();

    if (player->getPosition().Distance(position) < 50 && IsKeyPressed(KEY_E)) { // TODO: Make this distance a constant and add keyMap

        Item item = this->item.getItem().value();
        while (this->item.getCount() > 0) {

            this->item.setCount(this->item.getCount() - 1);
            player->getInventory()->addItem(item);

        }
        game->removeEntity(this);

    }

    

}

void DroppedItem::render()
{

    DrawTextureEx(item.getItem().value().getTexture(), {position.x, position.y}, 0, 32 / item.getItem().value().getTexture().width, raylib::Color(255, 255, 255, 255));

}

DroppedItem::DroppedItem(Slot item, raylib::Vector3 position, raylib::Vector3 velocity)
{

    this->item = item;
    this->position = position;
    this->velocity = velocity;

}