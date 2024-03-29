#pragma once


#include "Entity.hpp"


class Mineable : public Entity {

    public:

        Mineable(int x, int y, int health, const char* texture, Item dropped_item);
        ~Mineable();

        void update(Game* game) override;
        void render() override;

    protected:

        Item dropped_item;


};