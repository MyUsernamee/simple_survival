#pragma once

#include "Slot.hpp"
#include <array>

class Inventory {

    // TODO: 

    public:

        Inventory(char width, char height);
        Inventory() {}; // Classic C++
        ~Inventory();

        void clear(); // TODO: Implement

        std::optional<Item*> getItem(int index);
        std::optional<Item*> getItem(int x, int y);

        std::optional<Item*> popItem(int index);
        std::optional<Item*> popItem(int x, int y);

        Slot* getSlot(int index);
        Slot* getSlot(int x, int y);

        void addItem(Item* item);

        char getWidth() { return width; }
        char getHeight() { return height; }

        void render(int x, int y, int slot_width, int slot_height);

    private:

        int getIndex(int x, int y) { return y * width + x; }

        char width, height;
        int size;
        Slot** items;

};