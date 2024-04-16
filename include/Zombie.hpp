#pragma once


#include "Mob.hpp"


class Zombie: public Mob {

    public:

        Zombie(raylib::Vector2 position);

        void update_movement(Game* game);
        void render();

        void onMousePressed(Game* game, MouseButton button) { printf("Zombie clicked\n"); }
        void onMouseReleased(Game* game, MouseButton button) { printf("Zombie released\n"); }

        void onCollision(Entity* other) { printf("Zombie collided\n"); }

        void onDeath(Game* game);

    private:

};