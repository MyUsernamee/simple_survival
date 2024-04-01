#include <raylib-cpp.hpp>

#include <string>
#include <optional>

#pragma once


class Item {

    public:

        Item(std::string id, std::string name, std::optional<std::string> description, const char* texturePath);
        Item();

        virtual void use() {}; // Called when the player uses the item (Does nothing by default, but can be overridden by subclasses)

        Texture2D getTexture() { return texture; }
        std::string getName() { return name; }
        std::optional<std::string> getDescription() { return description; }
        std::string getId() { return id; }

        bool operator== (const Item& other) const { return id == other.id && name == other.name && description == other.description; }

    private:

        std::string id; // Unique identifier for the item class This is used to identify if the item is stacked etc. TODO: Find a better way to do this
        std::string name;
        std::optional<std::string> description;
        Texture2D texture;

};