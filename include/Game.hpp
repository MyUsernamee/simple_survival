#include <array>
#include <vector>

#pragma once

#include "Tile.hpp"
#include <raylib-cpp.hpp>

const unsigned short MAP_WIDTH = 256;
const unsigned char MAX_STACK_SIZE = 64;

const Color GRASS_COLOR = Color(80, 200, 80, 255);
const Color DIRT_COLOR = Color(139, 69, 19, 255);
const Color WATER_COLOR = Color(0, 0, 255, 255);

class Entity;
class Player;

class Game {

    //TODO : Add Pixelate Shader

    public:

        Game();
        Game(const char* filename); // Loads a map from a file (not implemented yet) (TODO: Implement map loading from file)
        static Game genFromLua(const char* filename); // Generates a game from a lua file

        void update(); // Renders and updates the game
        void render();

        double getDeltaTime() { return window->GetFrameTime(); } // Returns the time between frames
        
        bool shouldClose(); // Returns true if the game should close

        TileType getTile(int x, int y);
        void setTile(int x, int y, TileType tile);

        void addEntity(Entity* entity);
        void removeEntity(Entity* entity); // Removes an entity from the game

        std::vector<Entity*> getEntities() { return entities; }

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

        void generateWorld(); // Generates a world using tiles TODO: Implement this

        raylib::Vector2 getMousePosition(); // Returns the position of the mouse in the game world

        /**
         * @brief Returns a list of entities where the position is in the entities bounding box sorted by z-index.
        */
        std::vector<Entity*> getEntitiesAtMousePosition();
        std::vector<Entity*> getEntitiesAtPosition(raylib::Vector2 position);

        double getTime() { return time; }
        double getDays() { return days; }

        void setTime(double time) { this->time = time; }
        void setDays(double days) { this->days = days; }

        double getTimeOfDay() { return std::fmod(time, day_length); }
        double getDayProgress() { return time / day_length; }

    private:

        void doEntityVectorModification();

        Player* player;
        std::array<std::array<TileType, MAP_WIDTH>, MAP_WIDTH> tiles;
        raylib::Window* window;
        raylib::Camera2D* camera;
        std::vector<Entity*> entities;
        std::vector<Entity *> entities_to_add;
        std::vector<Entity *> entities_to_remove;

        double time;
        double days;

        const double day_length = 60.0 * 10.0; // 2 minutes per day

};