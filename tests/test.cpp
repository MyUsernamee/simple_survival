
#include "Slot.hpp"
#include <cassert>

int main () {

    Slot slot = Slot();
    slot.setItem(Item("sword", "Sword", nullptr, ""));
    slot.getItem();

    assert(slot.hasItem() == true);

    return 0;

}