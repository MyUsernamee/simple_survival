#pragma once

#include <vector>
#include "Item.hpp"

/**
 * @brief A recipe for crafting items.
 * Essentially a list of items that are required to craft a new item along with what entity you need to be by to craft it.
 * 
*/
class Recipe {

    public:

        Recipe();
        Recipe(std::vector<Item> ingredients, Item result);
        ~Recipe();

        std::vector<Item> getIngredients() { return ingredients; }
        Item getResult() { return result; }

        void render(int x, int y, int width, int height); // Render the recipe

    private:

        std::vector<Item> ingredients;
        Item result;

};