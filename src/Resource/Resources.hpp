#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>
#include <stdexcept>

struct Resource
{
    std::string name;
    std::string icon;
    float amount;

    Resource() : name(""), amount(0), icon("") {}

    Resource(std::string name, float amount, std::string icon)
        : name(name), amount(amount), icon(icon) {}

    Resource& operator+=(const Resource& other) {
        if (this->name == other.name && this->icon == other.icon) {
            this->amount += other.amount;
            return *this;
        } else {
            throw std::invalid_argument("Resources must have the same name and icon to be added.");
        }
        return *this;
    }

    friend Resource operator+(const Resource& lhs, const Resource& rhs) {
        if (lhs.name == rhs.name && lhs.icon == rhs.icon) {
            return Resource(lhs.name, lhs.amount + rhs.amount, lhs.icon);
        } else {
            throw std::invalid_argument("Resources must have the same name and icon to be added.");
        }
    }
};

struct WoodResource : public Resource
{
    WoodResource(float amount) : Resource("Wood", amount, "wood.png") {}
};

struct MineralResource : public Resource
{
    MineralResource(float amount) : Resource("Mineral", amount, "mineral.png") {}
};

struct FoodResource : public Resource
{
    FoodResource(float amount) : Resource("Food", amount, "meat.png") {}
};

#endif // RESOURCES_HPP
