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

    DrawRectangle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height), SLOT_BG_COLOR);

    if(item.has_value())
    {
        
        Texture2D item_texture = item.value()->getTexture();

        DrawTexturePro(item_texture, Rectangle{0, 0, static_cast<float>(item_texture.width), static_cast<float>(item_texture.height)}, Rectangle{static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)}, Vector2{0, 0}, 0, WHITE);

    }

}

Slot::Slot()
{
    item = std::nullopt;
    count = 0;
}