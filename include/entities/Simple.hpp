#pragma once
#include "Entity.hpp"

class Simple : public Entity {

    public:

        void update(Game* game);
        void render() override;

};