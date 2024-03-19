
#pragma once

enum TileType {
    GRASS,
    DIRT,
    WATER
};

class Tile {

    public:

        Tile();

        void render();
        void interact(); // Called when the player interacts with the tile (Does nothing by default, but can be overridden by subclasses)

        TileType getType() { return type; }

    private:

        TileType type;


};