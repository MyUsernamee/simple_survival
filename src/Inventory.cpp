#include "Inventory.hpp"
#include "Slot.hpp"

Inventory::Inventory(char width, char height)
{

    this->width = width;
    this->height = height;
    this->size = width * height;
    this->items = new Slot[width * height];

    for (int i = 0; i < width * height; i++)
    {

        items[i] = Slot();

    }

    this->item_map = std::map<Item, std::vector<int>>();

}

Inventory::~Inventory()
{

}

void Inventory::updateItemMap()
{

    item_map.clear();

    for (int i = 0; i < size; i++)
    {

        if (items[i].getItem().has_value())
        {

            if (item_map.find(items[i].getItem().value()) == item_map.end())
            {

                item_map[items[i].getItem().value()] = std::vector<int>();

            }

            item_map[items[i].getItem().value()].push_back(i);

        }

    }

}

void Inventory::setSlot(int index, Slot& slot)
{

    items[index] = slot;
    // Map the item
    updateItemMap(); // TODO: Optimize this

}

void Inventory::setSlot(int x, int y, Slot& slot)
{

    setSlot(getIndex(x, y), slot);

}

int Inventory::addItem(const Item& item)
{

    // Find the first free slot
    for (int i = 0; i < size; i++)
    {

        if (!items[i].getItem().has_value())
        {

            // Clone the item
            Item item_clone = item;
            items[i].setItem(item_clone);
            updateItemMap();
            return i;

        }

        if (items[i].getItem().value().getId() == item.getId() && items[i].getCount() < SLOT_MAX_COUNT)
        {

            items[i].add(1);
            updateItemMap();
            return i;

        }

    }

}

void Inventory::addItems(const Item& item, int count)
{

    for (int i = 0; i < size; i++)
    {

        if (items[i].getItem().has_value() && items[i].getItem().value().getId() == item.getId() && items[i].getCount() < SLOT_MAX_COUNT)
        {

            int to_add = std::min(SLOT_MAX_COUNT - items[i].getCount(), count);
            items[i].add(to_add);
            count -= to_add;

        }

        if (count == 0)
        {

            break;

        }

    }

    if (count > 0) // If there are still items to add meaning 
    {

        int index = addItem(item);
        items[index].setCount(count);

    }

    updateItemMap();

}

void Inventory::render(int x, int y, int slot_width, int slot_height)
{

    for (int i = 0; i < size; i++)
    {

        int slot_x = x + (i % width) * slot_width;
        int slot_y = y + (i / width) * slot_height;

        items[i].render(slot_x, slot_y, slot_width, slot_height);

    }

}

std::optional<Item> Inventory::getItem(int index)
{

    return items[index].getItem();

}

std::optional<Item> Inventory::getItem(int x, int y)
{

    return items[getIndex(x, y)].getItem();

}

std::optional<std::vector<Slot>> Inventory::find(Item item)
{

    if (item_map.find(item) != item_map.end()) // If the item exists in the inventory
    {

        std::vector<Slot> slots;

        for (int i = 0; i < item_map[item].size(); i++)
        {

            slots.push_back(items[item_map[item][i]]);

        }

        return slots;

    }

    return std::nullopt;

}

bool Inventory::has(Item item, int count)
{

    if (item_map.find(item) != item_map.end()) // If the item exists in the inventory
    {

        int total = 0;

        for (int i = 0; i < item_map[item].size(); i++)
        {

            total += items[item_map[item][i]].getCount();

        }

        return total >= count;

    }

    return false;

}

void Inventory::remove(Item item, int count)
{

    if (item_map.find(item) != item_map.end()) // If the item exists in the inventory
    {

        for (int i = 0; i < item_map[item].size(); i++) // Loop through all the slots that contain the item
        {

            if (items[item_map[item][i]].getCount() > count) // If the slot has enough items to remove
            {

                items[item_map[item][i]].remove(count); // Remove the items
                updateItemMap();
                return;

            }
            else
            {

                count -= items[item_map[item][i]].getCount(); // Remove the items from the count
                // Set that slot to an empty slot
                items[item_map[item][i]].setItem(std::nullopt);
                items[item_map[item][i]].setCount(0); // TODO: Make a clear function

                if (count == 0) // If all the items have been removed
                {

                    updateItemMap();
                    return;

                }

            }

        }

    }

}