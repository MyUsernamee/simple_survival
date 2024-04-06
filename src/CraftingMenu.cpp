#include "CraftingMenu.hpp"

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

    BeginTextureMode(texture);

    for(int i = 0; i < recipes.size(); i++)
    {
        Recipe recipe = recipes[i];
        recipe.render(0, i * 32, size.x, 32);
    }

    EndTextureMode();

}

void CraftingMenu::render()
{

    // Render the box
    DrawRectangle(position.x, position.y, size.x, size.y, UI_BG_COLOR);
    TraceLog(LOG_INFO, "Drawing crafting menu at %f, %f", position.x, position.y);

    DrawTexturePro(texture.texture, raylib::Rectangle{0, scroll, size.x, size.y + scroll}, raylib::Rectangle{0, 0, size.x, size.y}, raylib::Vector2{position.x, position.y}, 0, WHITE);

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
