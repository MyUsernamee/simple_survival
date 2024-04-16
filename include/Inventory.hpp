#pragma once

#include "Slot.hpp"
#include <array>
#include <map>

class Inventory {

    // TODO: 

    public:

        Inventory(char width, char height);
        Inventory() {}; // Classic C++
        ~Inventory();

        void clear(); // TODO: Implement
    
        std::optional<Item> getItem(int index);
        std::optional<Item> getItem(int x, int y);

        std::optional<Item> popItem(int index);
        std::optional<Item> popItem(int x, int y);

        Slot& getSlot(int index) { return items[index]; }
        Slot& getSlot(int x, int y) { return items[getIndex(x, y)]; }

        void setSlot(int index, Slot& slot);
        void setSlot(int x, int y, Slot& slot);

        /**
         * @brief Add an item to the inventory.
         * @return The index of the slot the item was added to.
        */
        int addItem(const Item& item);
        void addItems(const Item& item, int count);

        char getWidth() { return width; }
        char getHeight() { return height; }

        /**
         * @brief Find the first slot that contains the given item.
         * 
        */
        std::optional<std::vector<Slot>> find(Item item);

        /**
         * @brief Find the first slot that contains the given item.
         * 
        */
        bool has(Item item, int count);

        /**
         * @brief Remove the given item from the inventory.
         * This will remove the item from the first slot that contains it or the maximum amount of items from the inventory.
        */
        void remove(Item item, int count);

        void render(int x, int y, int slot_width, int slot_height);

        

    private:

        int getIndex(int x, int y) { return y * width + x; }

        char width, height;
        int size;
        Slot* items;
        std::map<Item, std::vector<int>> item_map; // Where is this item in the inventory?

        /**
         * @brief Update the item map.
         * TODO: Optimize this.
         * 
        */
        void updateItemMap();

};