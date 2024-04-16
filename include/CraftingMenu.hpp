#pragma once

#include "Entity.hpp"
#include "Recipe.hpp"


class CraftingMenu : public Entity {

    public:

        CraftingMenu(raylib::Vector2 position, raylib::Vector2 size, std::vector<Recipe> recipes);
        CraftingMenu();
        ~CraftingMenu();

        void update(Game *game);
        void render();

        void onMousePressed(Game *game, MouseButton button);

        void setRecipes(std::vector<Recipe> recipes);

    private:

        std::vector<Recipe> recipes;

        int scroll = 0;
        int selectedRecipe = -1;

        RenderTexture2D texture;
};