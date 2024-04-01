#include "Recipe.hpp"

#include "Colors.hpp"

void Recipe::render(int x, int y, int width, int height)
{

    DrawRectangle(x, y, width, height, UI_BG_COLOR);
    DrawRectangleLines(x, y, width, height, UI_BORDER_COLOR);

    

}