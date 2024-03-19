#include "Inventory.hpp"

Inventory::Inventory(char width, char height)
{

    this->width = width;
    this->height = height;
    this->items = new std::array<std::optional<Item*>, width * height>();

}

Inventory::~Inventory()
{

    delete items;

}

void Inventory::addItem(Item *item)
{

    

}
