#include "ButtonMenu.hpp"
#include "AssetManager.hpp"

ButtonMenu::ButtonMenu(std::string text, sf::Vector2f size, 
    std::function<void(std::vector<void*>)> cb, std::vector<void*> parameters) : frame(size),
    btnText(text, AssetManager::GetFont("anonymous.ttf"), 18), btnCb(cb), cbParameters(parameters)
{
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(5);

    if (frame.getSize().x < btnText.getLocalBounds().width + 20)
    {
        frame.setSize({btnText.getLocalBounds().width + 20, frame.getSize().y});
    }

    if (frame.getSize().y < btnText.getLocalBounds().height + 20)
    {
        frame.setSize({frame.getSize().x, btnText.getLocalBounds().height + 20});
    }

    frame.setOrigin(frame.getSize() * 0.5f);

    btnText.setOrigin({
        btnText.getLocalBounds().width * 0.5f,
        btnText.getLocalBounds().height * 0.5f
    });
    btnText.setFillColor(sf::Color::Black);
    btnText.setPosition(frame.getPosition());
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

#ifdef DEBUG
    auto debug = sf::RectangleShape({btnText.getLocalBounds().width, btnText.getLocalBounds().height});
    debug.setFillColor(sf::Color(1,1,1,0));
    debug.setOutlineColor(sf::Color::Red);
    debug.setOutlineThickness(3);
    debug.setOrigin(debug.getSize() * 0.5f);
    debug.setPosition(btnText.getPosition());
    target.draw(debug);
#endif
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
