#pragma once

#include <optional>

#include "Item.hpp"

class Slot {

    // TODO: IMPLEMENT ME!!!!

    public:

        Slot(Item* item, int count);

        std::optional<Item*> getItem() { return item; }
        int getCount() { return count; }

        void setItem(std::optional<Item*> item) { this->item = item; count = 1; }
        void setCount(int count) { this->count = count; }

        bool add(int count); // Add items, returns false if the slot is full
        bool remove(int count); // Remove items, returns false if the slot doesn't have enough items

    private:

        std::optional<Item*> item;
        int count;

};

