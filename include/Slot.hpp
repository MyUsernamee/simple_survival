#pragma once

#include <optional>

#include "Item.hpp"

const Color SLOT_BG_COLOR = GRAY;
const Color SLOT_BORDER_COLOR = DARKGRAY;

const int SLOT_MAX_COUNT = 64;

class Slot {

    // TODO: MOSTLY FINISHED, NEEDS TESTING

    public:

        Slot();

        std::optional<Item> getItem() { return item; }
        int getCount() { return count; }

        /**
         * @brief Set the item type of the slot.
         * 
        */
        void setItem(std::optional<Item> item) { this->item = item; count = 1; }

        /**
         * @brief Set the amount of that type of item in the slot.
         * 
        */
        void setCount(int count) { this->count = count; }

        bool add(int count); // Add items, returns false if the slot is full
        bool remove(int count); // Remove items, returns false if the slot doesn't have enough items

        bool hasItem() { return item.has_value() && count > 0; }

        /**
         * @brief Render the slot at the given position.
         * 
         * Mostly for debugging purposes, but might have a more flushed out use later.
        */
        void render(int x, int y, int width, int height); // TODO: Add a hover effect for the slot to show more data. Render item amount and count.

    private:

        std::optional<Item> item;
        int count;

};

