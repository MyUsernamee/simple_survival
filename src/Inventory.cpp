#include "Inventory.hpp"

Inventory::Inventory(char width, char height)
{

    this->width = width;
    this->height = height;
    this->size = width * height;
    this->items = new Slot*[width * height];

    for (int i = 0; i < width * height; i++)
    {

        items[i] = new Slot();

    }

}

Inventory::~Inventory()
{

    delete items;

}

void Inventory::addItem(Item *item)
{

    // Find the first free slot
    for (int i = 0; i < size; i++)
    {

        if (!items[i]->getItem().has_value())
        {

            items[i]->setItem(item);
            return;

        }

    }

}

void Inventory::render(int x, int y, int slot_width, int slot_height)
{

    for (int i = 0; i < size; i++)
    {

        int slot_x = x + (i % width) * slot_width;
        int slot_y = y + (i / width) * slot_height;

        items[i]->render(slot_x, slot_y, slot_width, slot_height);

    }

}