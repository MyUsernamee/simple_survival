#include "Item.hpp"

Item::Item(std::string id, std::string name, std::optional<std::string> description, const char *texturePath)
{

    this->id = id;
    this->name = name;
    this->description = description;
    this->texture = LoadTexture(texturePath);

}

Item::Item()
{

    this->id = "";
    this->name = "";
    this->description = "";
    this->texture = LoadTexture("");

}
