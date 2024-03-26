#pragma once


#include "Entity.hpp"
#include "Game.hpp"


class Dummy: public Entity {

    public:

        Dummy(raylib::Vector2 position, raylib::Vector2 size);

        void update(Game* game);
        void render();

    private:

        

};