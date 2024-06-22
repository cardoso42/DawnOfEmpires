#include "IncrementDecrementControl.hpp"

IncrementDecrementControl::IncrementDecrementControl(sf::Vector2f size, 
        std::string variableName, int *value, int minValue, int maxValue) 
    : value(value), frame(size), minValue(minValue), maxValue(maxValue),
    fastIncrementButton("++", {size.x * 0.1f, size.y}),
    incrementButton("+", {size.x * 0.1f, size.y}), 
    decrementButton("-", {size.x * 0.1f, size.y}),
    fastDecrementButton("--", {size.x * 0.1f, size.y})
{
    frame.setOrigin(frame.getLocalBounds().width / 2, frame.getLocalBounds().height / 2);
    
    incrementButton.setCallback([this](std::vector<void*> parameters) {
        auto value = (int*)parameters[0];
        auto maxValue = (int*)parameters[1];

        if (*value < *maxValue)
        {
            (*value)++;
        }
    }, std::vector<void*>{value, &this->maxValue});

    decrementButton.setCallback([this](std::vector<void*> parameters) {
        auto value = (int*)parameters[0];
        auto minValue = (int*)parameters[1];

        if (*value > *minValue)
        {
            (*value)--;
        }
    }, std::vector<void*>{value, &this->minValue});

    fastIncrementButton.setCallback([this](std::vector<void*> parameters) {
        auto value = (int*)parameters[0];
        auto maxValue = (int*)parameters[1];

        if (*value + 10 <= *maxValue)
        {
            (*value) += 10;
        }
        else
        {
            *value = *maxValue;
        }
    }, std::vector<void*>{value, &this->maxValue});

    fastDecrementButton.setCallback([this](std::vector<void*> parameters) {
        auto value = (int*)parameters[0];
        auto minValue = (int*)parameters[1];

        if (*value - 10 >= *minValue)
        {
            (*value) -= 10;
        }
        else
        {
            *value = *minValue;
        }
    }, std::vector<void*>{value, &this->minValue});

    valueText.setFont(AssetManager::GetFont("anonymous.ttf"));
    valueText.setCharacterSize(24);
    valueText.setString(variableName + ": " + std::to_string(*value));
    valueText.setOrigin(valueText.getLocalBounds().width / 2, valueText.getLocalBounds().height / 2);
    valueText.setFillColor(sf::Color::Black);
}

void IncrementDecrementControl::unselect()
{
    fastIncrementButton.unselect();
    incrementButton.unselect();
    decrementButton.unselect();
    fastDecrementButton.unselect();
}

sf::Vector2f IncrementDecrementControl::getSize()
{
    return {getGlobalBounds().width, getGlobalBounds().height};
}

void IncrementDecrementControl::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(fastIncrementButton);
    target.draw(fastDecrementButton);
    target.draw(incrementButton);
    target.draw(decrementButton);
    target.draw(valueText);
}

void IncrementDecrementControl::update()
{
    valueText.setString(valueText.getString().substring(0, valueText.getString().find(':') + 2) + std::to_string(*value));
    valueText.setOrigin(valueText.getLocalBounds().width / 2, valueText.getLocalBounds().height / 2);
    valueText.setPosition(frame.getPosition());

    incrementButton.update();
    decrementButton.update();
}

void IncrementDecrementControl::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    fastDecrementButton.setPosition({pos.x - frame.getSize().x / 2 + fastDecrementButton.getSize().x / 2 + 30, pos.y});
    decrementButton.setPosition({pos.x - frame.getSize().x / 2 + fastDecrementButton.getSize().x + 30 + decrementButton.getSize().x / 2 + 30, pos.y});
    incrementButton.setPosition({pos.x + frame.getSize().x / 2 - fastIncrementButton.getSize().x - 30 - incrementButton.getSize().x / 2 - 30, pos.y});
    fastIncrementButton.setPosition({pos.x + frame.getSize().x / 2 - fastIncrementButton.getSize().x / 2 - 30, pos.y});
    valueText.setPosition({pos.x, pos.y});
}

void IncrementDecrementControl::setColor(sf::Color color)
{
    frame.setFillColor(color);
}

sf::FloatRect IncrementDecrementControl::getGlobalBounds()
{
    return frame.getGlobalBounds();
}

sf::Color IncrementDecrementControl::getColor()
{
    return frame.getFillColor();
}

void IncrementDecrementControl::select(float x, float y)
{
    unselect();

    if (incrementButton.getGlobalBounds().contains(x, y))
    {
        incrementButton.select(x, y);
    }
    else if (decrementButton.getGlobalBounds().contains(x, y))
    {
        decrementButton.select(x, y);
    }
    else if (fastIncrementButton.getGlobalBounds().contains(x, y))
    {
        fastIncrementButton.select(x, y);
    }
    else if (fastDecrementButton.getGlobalBounds().contains(x, y))
    {
        fastDecrementButton.select(x, y);
    }
}
