#pragma once


#include "Entity.hpp"
#include "Game.hpp"


class Dummy: public Entity {

    public:

        Dummy(raylib::Vector2 position, raylib::Vector2 size);

        void update(Game* game);
        void render();

        void onMousePressed(Game* game, MouseButton button) { printf("Dummy clicked\n"); }
        void onMouseReleased(Game* game, MouseButton button) { printf("Dummy released\n"); }

    private:

        

};