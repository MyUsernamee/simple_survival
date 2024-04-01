#pragma once


#include "Entity.hpp"
#include "Item.hpp"

const int MINEABLE_SCALE = 4;

class Mineable : public Entity {

    public:

        Mineable(int x, int y, int health, const char* texture, Item dropped_item, int amount);
        ~Mineable();

        void update(Game* game) override;
        void render() override;

        raylib::Texture& getTexture() { return texture; }
        void setTexture(const char* texture) { this->texture = LoadTexture(texture); }

        Item getDroppedItem() { return dropped_item; }

        void onDeath(Game* game) override;

    protected:

        Item dropped_item; // TODO: Implement Mineable class
        raylib::Texture texture;
        int amount;


};