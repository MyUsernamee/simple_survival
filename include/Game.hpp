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
        Game(const char* filename); // Loads a map from a file (not implemented yet) (TODO: Implement map loading from file)
        static Game genFromLua(const char* filename); // Generates a game from a lua file

        void update(); // Renders and updates the game
        void render();

        double getDeltaTime() { return 1.0 / 60.0; } // Returns the time between frames
        
        bool shouldClose(); // Returns true if the game should close

        Tile* getTile(int x, int y);
        void setTile(int x, int y, Tile* tile);

        void addEntity(Entity* entity) { entities.push_back(entity); }

        Player* getPlayer() { return player; }

        // HECK IT WE ADD LUA!
        /**
         * 
         * @brief Runs a lua script. Will have to make API for this.
         * Why are we doing this?
         * When we are making this game, we want to be able to test things, so we will be able to run lua scripts to test things.
         * At some point might add a console, but probably not.
         * For now this will let us test things.
         * 
        */
        void runScript(const char* script); // TODO: Implement this


    private:

        Player* player;
        std::array<std::array<Tile*, MAP_WIDTH>, MAP_WIDTH> tiles;
        raylib::Window* window;
        raylib::Camera2D* camera;
        std::vector<Entity*> entities;

};