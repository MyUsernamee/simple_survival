#pragma once


#include "Entity.hpp"
#include "Item.hpp"

class Game; // Forward declaration

class DroppedItem : public Entity {

    public:

        DroppedItem(int x, int y, Item item);
        ~DroppedItem();

        void update(Game* game) override;
        void render() override;

        Item getItem() { return item; }

        void onCollision(Game* game, Entity* entity) override;

    protected:

        Item item;

};