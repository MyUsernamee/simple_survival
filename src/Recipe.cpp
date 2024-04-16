#include "Recipe.hpp"

#include "Colors.hpp"

void Recipe::render(int x, int y, int width, int height)
{

    DrawRectangle(x, y, width, height, UI_BG_COLOR);
    DrawRectangleLines(x, y, width, height, UI_BORDER_COLOR);

    // From the left 
    for(int i = 0; i < ingredients.size(); i++)
    {
        Slot slot = ingredients[i];
        slot.render(i * 16 + 8 + x, height / 2 - 8 + y, 16, 16);
    }

    // From the right
    result.render(width - 16 - 8 + x, height / 2 - 8 + y, 16, 16);

    raylib::Text text = raylib::Text("="); // TODO: Add a fun font to the game
    text.SetColor(WHITE);
    text.Draw(raylib::Vector2(width - 28 + x - text.MeasureEx().x / 2.0, height / 2 + y - text.MeasureEx().y / 2.0));

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