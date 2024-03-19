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