#pragma once


#include "Entity.hpp"
#include "Item.hpp"


class Mineable : public Entity {

    public:

        Mineable(int x, int y, int health, const char* texture, Item dropped_item);
        ~Mineable();

        void update(Game* game) override;
        void render() override;

        void onDeath(Game* game) override;

    protected:

        Item dropped_item; // TODO: Implement Mineable class


};