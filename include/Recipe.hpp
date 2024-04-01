#pragma once


/**
 * @brief A recipe for crafting items.
 * Essentially a list of items that are required to craft a new item along with what entity you need to be by to craft it.
 * 
*/
class Recipe {

    public:

        Recipe();
        Recipe(const char* name, const char* entity, const char* description, std::vector<Item> ingredients, Item result);
        ~Recipe();

        const char* getName() { return name; }
        const char* getEntity() { return entity; }
        const char* getDescription() { return description; }
        std::vector<Item> getIngredients() { return ingredients; }
        Item getResult() { return result; }

    private:

        const char* name;
        const char* entity;
        const char* description;
        std::vector<Item> ingredients;
        Item result;

};