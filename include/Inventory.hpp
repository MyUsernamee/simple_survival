#pragma once

#include "Slot.hpp"
#include <array>

class Inventory {

    // TODO: FIX ME, Change from item to slots and make implementation

    public:

        Inventory(char width, char height);
        ~Inventory();

        void addItem(Item* item);
        void clear();

        Item* getItem(int index);
        int getItemCount();

        Item* getItem(int x, int y);

        Item* popItem(int index);
        Item* popItem(int x, int y);

        Slot* getSlot(int index);
        Slot* getSlot(int x, int y);

        char getWidth() { return width; }
        char getHeight() { return height; }

    private:

        char width, height;
        std::array<Slot*, width * height>* items;

};