#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>
#include <stdexcept>

class Resource
{
public:
    Resource() : name(""), amount(0), icon("") {}

    Resource(std::string name, float amount, std::string icon)
        : name(name), amount(amount), icon(icon) {}

    std::string getName() { return name; }
    std::string getIcon() { return icon; }
    float getAmount() { return amount; }

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

    Resource& operator+=(const int& amount)
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

    Resource& operator-=(const int& amount)
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
    NullResource() : Resource("Null", 0, "") {}
};

#endif // RESOURCES_HPP