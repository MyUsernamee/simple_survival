#include "Recipe.hpp"

#include "Colors.hpp"

void Recipe::render(int x, int y, int width, int height)
{

    DrawRectangle(x, y, width, height, UI_BG_COLOR);
    DrawRectangleLines(x, y, width, height, UI_BORDER_COLOR);

    raylib::RenderTexture render_texture(width, height);

    render_texture.BeginMode();

    // From the left 
    for(int i = 0; i < ingredients.size(); i++)
    {
        Slot slot = ingredients[i];
        slot.render(i * 16 + 8, height / 2 - 8, 16, 16);
    }

    // From the right
    result.render(width - 16 - 8, height / 2 - 8, 16, 16);

    render_texture.EndMode();

    DrawTexture(render_texture.getTexture(), x, y, WHITE);
}

Recipe::Recipe(std::vector<Slot> ingredients, Slot result)
{
    this->ingredients = ingredients;
    this->result = result;
}

Recipe::~Recipe()
{
    // Do nothing
}