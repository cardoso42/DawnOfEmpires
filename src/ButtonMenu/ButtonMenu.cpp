#include "ButtonMenu.hpp"
#include "AssetManager.hpp"

ButtonMenu::ButtonMenu(std::string text, sf::Vector2f size, 
    std::function<void(std::vector<void*>)> cb, std::vector<void*> parameters) : frame(size),
    btnText(text, AssetManager::GetFont("anonymous.ttf"), 18), btnCb(cb), cbParameters(parameters)
{
    frame.setOrigin(size * 0.5f);
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(5);

    btnText.setOrigin({
        btnText.getLocalBounds().width * 0.5f,
        btnText.getLocalBounds().height * 0.5f
    });
    btnText.setFillColor(sf::Color::Black);
}

void ButtonMenu::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    btnText.setPosition(pos);
}

void ButtonMenu::setScale(sf::Vector2f scale)
{
    frame.setScale(scale);
    btnText.setScale(scale);
}

void ButtonMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame);
    target.draw(btnText);
}

void ButtonMenu::select()
{
    frame.setOutlineColor(sf::Color::Magenta);
    frame.setOutlineThickness(12);

    if (btnCb)
    {
        btnCb(cbParameters);
    }
}

void ButtonMenu::unselect()
{
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(5);
}

sf::FloatRect ButtonMenu::getGlobalBounds() { return frame.getGlobalBounds(); }

sf::Vector2f ButtonMenu::getSize() { return frame.getSize(); }
