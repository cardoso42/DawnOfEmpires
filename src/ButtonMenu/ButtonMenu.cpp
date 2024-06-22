#include "ButtonMenu.hpp"
#include "AssetManager.hpp"

ButtonMenu::ButtonMenu(std::string text, sf::Vector2f size, bool visible) : 
    btnText(text, AssetManager::GetFont("anonymous.ttf"), 18), selectable(true),
    btnCb(nullptr), cbParameters({}), isSelected(false), frame(size), isVisible(visible)
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

    if (!isVisible)
    {
        frame.setFillColor(sf::Color(0, 0, 0, 0));
    }
}

void ButtonMenu::setCallback(CallbackFunction cb, std::vector<void *> parameters)
{
    btnCb = cb;
    cbParameters = parameters;
}

void ButtonMenu::setSelectable(bool selectable) { this->selectable = selectable; }

void ButtonMenu::update()
{
}

void ButtonMenu::setOutlineThickness(float thickness) { frame.setOutlineThickness(thickness); }

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

void ButtonMenu::setColor(sf::Color color)
{
    if (!isVisible)
    {
        color.a = 0;
    }
    
    frame.setFillColor(color);
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

void ButtonMenu::select(float x, float y)
{
    if (!selectable || isSelected)
    {
        return;
    }

    isSelected = true;
    frame.setOutlineColor(sf::Color::Magenta);
    frame.setOutlineThickness(frame.getOutlineThickness() * 2);

    if (btnCb != nullptr)
    {
        btnCb(cbParameters);
    }
}

void ButtonMenu::unselect()
{
    if (!selectable || !isSelected)
    {
        return;
    }
    
    isSelected = false;
    frame.setOutlineColor(sf::Color::Black);
    frame.setOutlineThickness(frame.getOutlineThickness() / 2);
}

void ButtonMenu::updateText(std::string newText)
{
    btnText.setString(newText);

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
    btnText.setPosition(frame.getPosition());
}

sf::FloatRect ButtonMenu::getGlobalBounds() { return frame.getGlobalBounds(); }

sf::Vector2f ButtonMenu::getSize() { return frame.getSize(); }

std::string ButtonMenu::getText()
{
    return btnText.getString();
}

sf::Color ButtonMenu::getColor()
{
    return frame.getFillColor();
}
