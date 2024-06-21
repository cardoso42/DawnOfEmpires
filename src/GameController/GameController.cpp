#include "GameController.hpp"
#include "ContextMenu.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): currentPressedKey(sf::Keyboard::Key::Unknown),  
    wasMouseButtonAlreadyPressed(false), windowManager(GameContext::getWindowManager())
{
    windowManager.createView("mainMenu", {0, 0}, {1, 1});
    components["mainMenu"] = new MainMenu(windowManager.getViewSize("mainMenu"));

    // TODO: update keyactions depending on the current context
    keyActions = {
        {sf::Keyboard::S, []() { ActionMenu::selectInitialTileBtnCb({}); }},
        {sf::Keyboard::I, []() { ActionMenu::improveTileBtnCb({}); }},
        {sf::Keyboard::A, []() { ActionMenu::annexTileBtnCb({}); }},
        {sf::Keyboard::C, []() { ActionMenu::constructCultureTileBtnCb({}); }},
        {sf::Keyboard::M, []() { ActionMenu::constructMilitaryTileBtnCb({}); }},
        {sf::Keyboard::E, []() { ActionMenu::constructEconomyTileBtnCb({}); }},
        {sf::Keyboard::G, []() { ActionMenu::spendGoldCoinBtnCb({}); }},
        {sf::Keyboard::N, []() { ActionMenu::nextTurnBtnCb({}); }},
        {sf::Keyboard::Left, [this]() { components["map"]->handleKeyboardInput(sf::Keyboard::Left); }},
        {sf::Keyboard::Right, [this]() { components["map"]->handleKeyboardInput(sf::Keyboard::Right); }},
        {sf::Keyboard::Up, [this]() { components["map"]->handleKeyboardInput(sf::Keyboard::Up); }},
        {sf::Keyboard::Down, [this]() { components["map"]->handleKeyboardInput(sf::Keyboard::Down); }},
    };

    music.openFromFile(AssetManager::GenerateAbsolutePathname("backgroundMusic.mp3"));
    music.setLoop(true);

    // TODO: add menu pressing ESC (control volume, etc)
    // TODO: save last selected tile from player to restaure it when its their turn again, also center the map on it
    // TODO: on game context, do not allow to map size be bigger than a number and players bigger than the amount of colors available
    // TODO: find out why the color of the player disappeared from the help area
    // TODO: check if culture bonus is really working
    // TODO: lower even more the amount in each resource source
}

GameController::~GameController()
{
}

void GameController::updateFrame(sf::Time deltaTime)
{
    windowManager.update();

    for (auto& [name, component] : components)
    {
        component->update();
        component->animate(deltaTime);
    }
}

void GameController::render(sf::Color backgroundColor)
{
    windowManager.beginDraw();

    for (auto& [name, component] : components)
    {
        windowManager.switchToView(name);
        windowManager.draw(*component);
    }
    
    windowManager.endDraw();
}

void GameController::handleInput()
{
    auto events = GameContext::getEvents();
    for (auto& event : events)
    {
        switch (event)
        {
            case GameContext::GameEvents::GAME_OVER:
                music.stop();

                for (auto& [name, component] : components)
                {
                    delete component;
                    windowManager.removeView(name);
                }
                components.clear();

                windowManager.createView("mainMenu", {0, 0}, {1, 1});
                components["mainMenu"] = new MainMenu(windowManager.getViewSize("mainMenu"));
                break;

            case GameContext::GameEvents::GAME_STARTED:
                for (auto& [name, component] : components)
                {
                    delete component;
                    windowManager.removeView(name);
                }
                components.clear();

                windowManager.createView("map", {0, 0}, {0.8, 0.9});
                windowManager.createView("actionMenu", {0.8, 0.3}, {0.2, 0.6});
                windowManager.createView("resources", {0, 0.9}, {1, 0.1});
                windowManager.createView("help", {0.8, 0}, {0.2, 0.3});

                components["map"] = new TileMap(GameContext::getMapSize(), windowManager.getViewSize("map") * 0.5f);
                components["actionMenu"] = new ActionMenu(windowManager.getViewSize("actionMenu"));
                components["resources"] = new ResourceBar(windowManager.getViewSize("resources"));
                components["help"] = new HelpArea(windowManager.getViewSize("help"));

                music.play();
                break;
            
            case GameContext::GameEvents::NEXT_TURN:
                // It is possible to use this event to update the resources bar only at this moment
                // I think it would be more efficient, but I don't know if this is a priority right now
                break;

            case GameContext::GameEvents::QUIT:
                windowManager.close();
                break;

            default:
                break;
        }
    }

    if (windowManager.isFocused())
    {
        handleMouseInput();
        handleKeyboardInput();
    }
}

void GameController::handleMouseInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        // Basically, act only when the button is first pressed
        // This is to avoid multiple calls for this block of code,
        // for example, to avoid multiple buttons clicks

        if (!wasMouseButtonAlreadyPressed) 
        {
            wasMouseButtonAlreadyPressed = true;
            sf::Vector2i pos = sf::Mouse::getPosition(windowManager);
            sf::Vector2f sceneCords;

            for (auto& [name, component] : components)
            {
                if (windowManager.getViewport(name).contains(pos))
                {
                    windowManager.switchToView(name);
                    sceneCords = windowManager.mapPixelToCoords({pos.x, pos.y});
                    component->click(sceneCords.x, sceneCords.y);
                }
            }
        }
    } 
    else 
    {
        wasMouseButtonAlreadyPressed = false;
    }
}

void GameController::handleKeyboardInput()
{
    for (const auto& [key, action] : keyActions) 
    {
        if (sf::Keyboard::isKeyPressed(key)) 
        {
            if (currentPressedKey == sf::Keyboard::Key::Unknown)
            {
                action();
                currentPressedKey = key;
            }

            return;
        }
    }

    currentPressedKey = sf::Keyboard::Key::Unknown;
}

sf::RectangleShape GameController::drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor)
{
    sf::RectangleShape outline({
        sprite.getGlobalBounds().width,
        sprite.getGlobalBounds().height
    });

    outline.setFillColor(backgroundColor);
    outline.setOutlineThickness(2);
    outline.setOutlineColor(sf::Color::Red);
    outline.setPosition(sprite.getPosition());
    outline.setOrigin(outline.getSize() * 0.5f);

    return outline;
}

bool GameController::isOver() { return windowManager.isDone(); }
