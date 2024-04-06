#include "CraftingMenu.hpp"
#include "Game.hpp"


CraftingMenu::CraftingMenu(raylib::Vector2 position, raylib::Vector2 size, std::vector<Recipe> recipes)
{

    this->position = position;
    this->size = size;
    this->recipes = recipes;
    
    this->texture = LoadRenderTexture(size.x, size.y + recipes.size() * 32);
    this->collisionBitMask = 0; // No collision

}

CraftingMenu::~CraftingMenu()
{
    // Do nothing
}

void CraftingMenu::update(Game *game)
{
    
    scroll += GetMouseWheelMove() * 32;

}

void CraftingMenu::render()
{

    // Render the box
    DrawRectangle(position.x, position.y, size.x, size.y, UI_BG_COLOR);
    ///TraceLog(LOG_INFO, "Drawing crafting menu at %f, %f", position.x, position.y);

    // Render the recipes
    for (int i = scroll / 32; i < recipes.size(); i++)
    {

        Recipe recipe = recipes[i];

        // Draw the recipe
        recipe.render(position.x, position.y + i * 32 - scroll, size.x, 32);

        if (32 * i > size.y + scroll) {
            break;
        }

    }

}

CraftingMenu::CraftingMenu()
{
    // Do nothing
}

void CraftingMenu::onMousePressed(Game *game, MouseButton button)
{
    // Do nothing
}

void CraftingMenu::setRecipes(std::vector<Recipe> recipes)
{

    this->recipes = recipes;
    // Resize the texture
    UnloadRenderTexture(texture);
    this->texture = LoadRenderTexture(size.x, size.y + recipes.size() * 32);
    

}
