#pragma once

#include <vector>
#include "Item.hpp"
#include "Slot.hpp"

/**
 * @brief A recipe for crafting items.
 * Essentially a list of items that are required to craft a new item along with what entity you need to be by to craft it.
 * 
*/
class Recipe {

    public:

        Recipe(std::vector<Slot> ingredients, Slot result);
        ~Recipe(); // TODO: We are going to have to implement proper destructors at some point.

        std::vector<Slot> getIngredients() { return ingredients; }
        Slot getResult() { return result; }

        void render(int x, int y, int width, int height); // Render the recipe

    private:

        std::vector<Slot> ingredients;
        Slot result;

};