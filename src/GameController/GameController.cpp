#include "GameController.hpp"
#include "WinnerScreen.hpp"
#include "PauseMenu.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): currentPressedKey(sf::Keyboard::Key::Unknown),  
    wasMouseButtonAlreadyPressed(false), musicPlayingWhenPaused(false)
{
    windowManager = GameContext::getWindowManager();

    windowManager->createView("mainMenu", {0, 0}, {1, 1});
    components["mainMenu"] = new MainMenu(windowManager->getViewSize("mainMenu"));
    currentState = State::MAIN_MENU;

    music.openFromFile(AssetManager::GenerateAbsolutePathname("backgroundMusic.mp3"));
    music.setLoop(true);
}

GameController::~GameController()
{
}

void GameController::updateFrame(sf::Time deltaTime)
{
    windowManager->update();

    for (auto& [name, component] : components)
    {
        component->update();
        component->animate(deltaTime);
    }
}

void GameController::render(sf::Color backgroundColor)
{
    windowManager->beginDraw();

    for (auto& [name, component] : components)
    {
        windowManager->switchToView(name);
        windowManager->draw(*component);
    }
    
    windowManager->endDraw();
}

void GameController::handleInput()
{
    auto events = GameContext::getEvents();
    for (auto& event : events)
    {
        switch (event)
        {
            case GameContext::GameEvents::GAME_OVER:
                handleGameOver();
                currentState = State::WINNER_SCREEN;
                break;

            case GameContext::GameEvents::GAME_STARTED:
                handleGameStarted();
                currentState = State::GAME_RUNNING;
                break;

            case GameContext::GameEvents::NEXT_TURN:
                handleNextTurn();
                break;

            case GameContext::GameEvents::QUIT:
                handleGameQuit();
                break;

            case GameContext::GameEvents::MAIN_MENU:
                handleMainMenu();
                currentState = State::MAIN_MENU;
                break;

            case GameContext::GameEvents::PAUSE:
                if (currentState == State::GAME_RUNNING)
                {
                    handleGamePaused();
                    currentState = State::PAUSE_MENU;
                }
                break;

            case GameContext::GameEvents::RESUME:
                handleGameResumed();
                currentState = State::GAME_RUNNING;
                break;

            default:
                break;
        }

        addEscapeKeybinding();
    }

    if (windowManager->isFocused())
    {
        handleMouseInput();
        handleKeyboardInput();
    }
}

void GameController::clearComponents()
{
    for (auto& [name, component] : components)
    {
        delete component;
        windowManager->removeView(name);
    }
    components.clear();
}

void GameController::saveCurrentComponents()
{
    for (auto& [name, component] : components)
    {
        savedComponents[name] = component;
    }
    components.clear();
}

void GameController::restoreSavedComponents()
{
    clearComponents();

    for (auto& [name, component] : savedComponents)
    {
        components[name] = component;
    }

    savedComponents.clear();
}

void GameController::clearSavedComponents()
{
    for (auto& [name, component] : savedComponents)
    {
        delete component;
        windowManager->removeView(name);
    }
    savedComponents.clear();
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
            sf::Vector2i pos = sf::Mouse::getPosition(*windowManager);
            sf::Vector2f sceneCords;

            for (auto& [name, component] : components)
            {
                if (windowManager->getViewport(name).contains(pos))
                {
                    windowManager->switchToView(name);
                    sceneCords = windowManager->mapPixelToCoords({pos.x, pos.y});
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
    auto keyActions = GameContext::getKeyActions();
    for (const auto& [key, action] : keyActions) 
    {
        if (sf::Keyboard::isKeyPressed(key)) 
        {
            if (currentPressedKey == sf::Keyboard::Key::Unknown)
            {
                action.first(action.second);
                currentPressedKey = key;
            }

            return;
        }
    }

    currentPressedKey = sf::Keyboard::Key::Unknown;
}

void GameController::handleGameOver()
{
    music.stop();

    clearComponents();

    windowManager->createView("winnerScreen", {0, 0}, {1, 1});
    components["winnerScreen"] = new WinnerScreen(
        windowManager->getViewSize("winnerScreen"), GameContext::getWinnerPlayer());
}

void GameController::handleGameStarted()
{
    clearComponents();

    windowManager->createView("map", {0, 0}, {0.8, 0.9});
    windowManager->createView("actionMenu", {0.8, 0.3}, {0.2, 0.6});
    windowManager->createView("resources", {0, 0.9}, {1, 0.1});
    windowManager->createView("help", {0.8, 0}, {0.2, 0.3});

    components["map"] = new TileMap(GameContext::getMapSize(), windowManager->getViewSize("map") * 0.5f);
    components["actionMenu"] = new ActionMenu(windowManager->getViewSize("actionMenu"));
    components["resources"] = new ResourceBar(windowManager->getViewSize("resources"));
    components["help"] = new HelpArea(windowManager->getViewSize("help"));

    music.play();
}

void GameController::handleNextTurn()
{
    // Restores the last selected tile of the current player
    auto it = components.find("map");
    if (it == components.end())
        throw std::logic_error("Map component not found");
    
    auto map = dynamic_cast<TileMap*>(it->second);
    map->selectTile(GameContext::getPlayer()->getLastSelectedTile());
    windowManager->centerOnSelectedTile();

    // It is possible to use this event to update the resources bar only at this moment
    // I think it would be more efficient, but I don't know if this is a priority right now
}

void GameController::handleGameQuit()
{
    windowManager->close();
}

void GameController::handleMainMenu()
{
    music.stop();

    clearComponents();
    clearSavedComponents();

    windowManager->createView("mainMenu", {0, 0}, {1, 1});
    components["mainMenu"] = new MainMenu(windowManager->getViewSize("mainMenu"));

    IdGenerator::ResetEmpireIds();
}

void GameController::handleGamePaused()
{
    if (currentState != State::GAME_RUNNING)
    {
        return;
    }

    musicPlayingWhenPaused = music.getStatus() == sf::Music::Playing;
    music.pause();

    saveCurrentComponents();
    windowManager->saveCurrentViews();

    windowManager->createView("pauseMenu", {0, 0}, {1, 1});
    components["pauseMenu"] = new PauseMenu(windowManager->getViewSize("pauseMenu"));
}

void GameController::handleGameResumed()
{
    if (currentState != State::PAUSE_MENU)
    {
        return;
    }

    if (musicPlayingWhenPaused)
    {
        music.play();
    }

    restoreSavedComponents();
    windowManager->restoreSavedViews();

    music.setVolume(GameContext::getMusicVolume());
}

void GameController::addEscapeKeybinding()
{
    if (currentState == State::PAUSE_MENU)
    {
        GameContext::addKeyAction(
            sf::Keyboard::Key::Escape,
            [](std::vector<void*>) 
            { 
                GameContext::notifyEvent(GameContext::GameEvents::RESUME); 
            }
        );
    }
    else if (currentState == State::GAME_RUNNING)
    {
        GameContext::addKeyAction(
            sf::Keyboard::Key::Escape,
            [](std::vector<void*>) 
            { 
                GameContext::notifyEvent(GameContext::GameEvents::PAUSE); 
            }
        );
    }
    else
    {
        GameContext::removeKeyAction(sf::Keyboard::Key::Escape);
    }
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

bool GameController::isOver() { return windowManager->isDone(); }
