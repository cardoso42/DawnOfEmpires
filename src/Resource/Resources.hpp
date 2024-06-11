#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>
#include <stdexcept>

class Resource
{
public:
    Resource() : name(""), amount(0), icon(""), isVisible(false) {}

    Resource(std::string name, float amount, std::string icon, bool isVisible = true)
        : name(name), amount(amount), icon(icon), isVisible(isVisible) {}

    std::string getName() { return name; }
    std::string getIcon() { return icon; }
    float getAmount() { return amount; }
    bool getVisibility() { return isVisible; }

    Resource& operator+=(const Resource& other) 
    {
        if (this->name == other.name && this->icon == other.icon) 
        {
            this->amount += other.amount;
            return *this;
        } 
        else 
        {
            throw std::invalid_argument("Resources must have the same name and icon to be added.");
        }
        return *this;
    }

    Resource& operator+=(const float& amount)
    {
        this->amount += amount;
        return *this;
    }

    Resource& operator-=(const Resource& other)
    {
        if (this->name == other.name && this->icon == other.icon)
        {
            this->amount -= other.amount;
            return *this;
        }

        return *this;
    }

    Resource& operator-=(const float& amount)
    {
        this->amount -= amount;
        return *this;
    }
    
    friend Resource operator-(const Resource& lhs, Resource& rhs)
    {
        if (lhs.name == rhs.name && lhs.icon == rhs.icon)
        {
            return Resource(lhs.name, lhs.amount - rhs.amount, lhs.icon);
        } 
        else 
        {
            throw std::invalid_argument("Resources must have the same name and icon to be subtracted.");
        }
    }

    friend Resource operator+(const Resource& lhs, const Resource& rhs) 
    {
        if (lhs.name == rhs.name && lhs.icon == rhs.icon) 
        {
            return Resource(lhs.name, lhs.amount + rhs.amount, lhs.icon);
        } 
        else 
        {
            throw std::invalid_argument("Resources must have the same name and icon to be added.");
        }
    }
private:
    friend class ResourceSource;

    std::string name;
    std::string icon;
    float amount;
    bool isVisible;
};

class WoodResource : public Resource
{
public:
    WoodResource(float amount) : Resource("Wood", amount, "wood.png") {}
};

class MineralResource : public Resource
{
public:
    MineralResource(float amount) : Resource("Mineral", amount, "mineral.png") {}
};

class FoodResource : public Resource
{
public:
    FoodResource(float amount) : Resource("Food", amount, "meat.png") {}
};

class HumanResource : public Resource
{
public:
    HumanResource(float amount) : Resource("Human", amount, "human.png") {}
};

class NullResource : public Resource
{
public:
    NullResource() : Resource("Null", 0, "", false) {}
};

class TileResource : public Resource
{
public:
#ifdef DEBUG
    TileResource(float amount) : Resource("Tile", amount, "tile.png") {}
#else
    TileResource(float amount) : Resource("Tile", amount, "tile.png", false) {}
#endif
};

class GoldResource : public Resource
{
public:
    GoldResource(float amount) : Resource("Gold", amount, "gold.png") {}
};

class CultureBonusResource : public Resource
{
public:
#ifdef DEBUG
    CultureBonusResource(float amount) : Resource("CultureBonus", amount, "culture.png") {}
#else
    CultureBonusResource(float amount) : Resource("CultureBonus", amount, "culture.png", false) {}
#endif
};

#endif // RESOURCES_HPP
