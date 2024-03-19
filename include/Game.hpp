#include <array>
#include <vector>

#pragma once

#include "Player.hpp"
#include "Tile.hpp"
#include "Entity.hpp"

class Entity; // Forward declaration

const unsigned short MAP_WIDTH = 256;
const unsigned char MAX_STACK_SIZE = 64;

class Game {

    public:

        Game();
        Game(const char* filename); // Loads a map from a file (not implemented yet)

        void update(); // Renders and updates the game
        void render();

        double getDeltaTime() { return 1.0 / 60.0; } // Returns the time between frames
        
        bool shouldClose(); // Returns true if the game should close

        Tile* getTile(int x, int y);
        void setTile(int x, int y, Tile* tile);

        void addEntity(Entity* entity) { entities.push_back(entity); }

    private:

        Player* player;
        std::array<std::array<Tile*, MAP_WIDTH>, MAP_WIDTH> tiles;
        raylib::Window* window;
        raylib::Camera2D* camera;
        std::vector<Entity*> entities;

};