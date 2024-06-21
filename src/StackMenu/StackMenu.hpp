#ifndef STACKMENU_HPP
#define STACKMENU_HPP

#include "BaseComponent.hpp"
#include <GenericMenu.hpp>

class StackMenu : public BaseComponent
{
public:
    StackMenu(GenericMenu *startingMenu);

    void addMenu(GenericMenu *menu);
    void goBack();
    
    void update() override;
    void animate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;
    void click(float x, float y) override;

private:
    std::vector<GenericMenu*> menus;
};

#endif // STACKMENU_HPP
