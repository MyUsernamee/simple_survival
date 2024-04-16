#include "Slot.hpp"

bool Slot::add(int count)
{
    this->count += count;

    if(this->count > 64)
    {
        this->count = 64;
        return false;
    }

    return true;

}

bool Slot::remove(int count)
{
    this->count -= count;

    if(this->count < 0)
    {
        this->count = 0;
        return false;
    }

    return true;

}

void Slot::render(int x, int y, int width, int height)
{

    DrawRectangle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height), UI_BG_COLOR);

    if(item.has_value())
    {
        
        

        Texture2D item_texture = item.value().getTexture();
        DrawTextureEx(item_texture, {static_cast<float>(x), static_cast<float>(y)}, 0, (static_cast<float>(width) / item_texture.width), WHITE);
        
        // If it doesn't have a texture, draw a placeholder
        if(item_texture.id == 0)
        {
            DrawText("?", x + width / 2 - MeasureText("?", height) / 2, y + height / 2 - height / 4, height / 2, WHITE);
        }

        std::string count_str = std::to_string(count);

        int text_width = MeasureText(count_str.c_str(), height / 4);

        DrawText(std::to_string(count).c_str(), x + width - text_width - 2, y + height - height / 2, height / 4, WHITE);

    }

    DrawRectangleLines(x, y, width, height, UI_BORDER_COLOR);

}

void Slot::renderTooltip(int x, int y, int width, int height)
{

    DrawRectangle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height), BLACK);

    if(item.has_value())
    {
        

        DrawText(item.value().getName().c_str(), x + 2, y + 2, height / 4, WHITE);
        DrawText(item.value().getDescription().value_or("No Description").c_str(), x + 2, y + 2 + height / 4, height / 4, WHITE);

    }

    DrawRectangleLines(x, y, width, height, WHITE);
    
}

void Slot::render(int x, int y, int width, int height, raylib::Vector2 mouse_position)
{

    render (x, y, width, height);

    if(mouse_position.x >= x && mouse_position.x <= x + width && mouse_position.y >= y && mouse_position.y <= y + height)
    {

        renderTooltip(x, y, width, height); // TODO: Add this to every slot somehow.

    }

}

Slot::Slot()
{
    item = std::nullopt;
    count = 0;
}

Slot::Slot(std::optional<Item> item, int count)
{

    this->item = item;
    this->count = count;

}
