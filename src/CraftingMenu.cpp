#include "CraftingMenu.hpp"
#include "Game.hpp"
#include "Player.hpp"

CraftingMenu::CraftingMenu(raylib::Vector2 position, raylib::Vector2 size, std::vector<Recipe> recipes)
{

    this->position = position;
    this->size = size;
    this->recipes = recipes;
    this->selectedRecipe = -1;
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

    if (this->contains(game->getMousePosition()))
    {
        selectedRecipe = (game->getMousePosition().y - position.y + scroll + size.y / 2) / 32;
    }
    else {
        selectedRecipe = -1;
    }

}

void CraftingMenu::render()
{

    // Render the box
    DrawRectangle(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, UI_BG_COLOR);
    ///TraceLog(LOG_INFO, "Drawing crafting menu at %f, %f", position.x, position.y);

    // Render the recipes
    for (int i = scroll / 32; i < recipes.size(); i++)
    {

        Recipe recipe = recipes[i];

        // Draw the recipe
        recipe.render(position.x - size.x / 2, position.y + i * 32 - scroll - size.y / 2, size.x, 32);

        if (i == selectedRecipe)
        {
            DrawRectangle(position.x - size.x / 2, position.y + i * 32 - scroll - size.y / 2, size.x, 32, {0, 0, 0, 128});
        }

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
    
    if (selectedRecipe != -1 && button == MOUSE_BUTTON_LEFT && selectedRecipe < recipes.size())
    {
        Recipe recipe = recipes[selectedRecipe];
        Player* player = game->getPlayer();

        // Check if the player has the ingredients
        for (Slot slot : recipe.getIngredients())
        {
            if (!player->getInventory()->has(slot.getItem().value(), slot.getCount()))
            {
                return;
            }
        }

        // Remove the ingredients
        for (Slot slot : recipe.getIngredients())
        {
            player->getInventory()->remove(slot.getItem().value(), slot.getCount());
        }

        // Add the result
        auto result = recipe.getResult(); // Store the result in a variable
        player->getInventory()->addItems(result.getItem().value(), result.getCount());

    }

}

void CraftingMenu::setRecipes(std::vector<Recipe> recipes)
{

    this->recipes = recipes;
    // Resize the texture
    UnloadRenderTexture(texture);
    this->texture = LoadRenderTexture(size.x, size.y + recipes.size() * 32);
    

}
