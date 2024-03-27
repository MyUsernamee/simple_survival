#pragma once

#include "Entity.hpp"

class Mob : public Entity {

    public:

        void update(Game* game);
        void render();

        /**
         * @brief Update the movement of the mob / behavior. This is called whenever the mob is is living and able to move.
        */
        virtual void update_movement(Game* game) = 0;

        void onMousePressed(Game* game, MouseButton button) { printf("Mob clicked\n"); }
        void onMouseReleased(Game* game, MouseButton button) { printf("Mob released\n"); }

    private:

        raylib::Vector2 movement;
        double speed;

};