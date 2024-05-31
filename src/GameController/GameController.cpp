#include "GameController.hpp"
#include "ContextMenu.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): windowManager("Dawn of Empires"), 
    wasMouseButtonAlreadyPressed(false), hasPlayerWon(false)
{
    windowManager.createView("map", {0, 0}, {0.8, 0.9});
    windowManager.createView("menu", {0.8, 0.3}, {0.2, 0.6});
    windowManager.createView("resources", {0, 0.9}, {1, 0.1});
    windowManager.createView("help", {0.8, 0}, {0.2, 0.3});

    players.push_back(Empire());
    GameContext::setEmpire(&players[0]);
    
    int mapRadius = 15;
    map = new TileMap(mapRadius, windowManager.getViewSize("map") * 0.5f);
    menu = new ActionMenu(windowManager.getViewSize("menu"));
    bar = new ResourceBar(windowManager.getViewSize("resources"));
    help = new HelpArea(windowManager.getViewSize("help"));
}

GameController::~GameController()
{
    delete map;
    delete menu;
    delete bar;
    delete help;
}

void GameController::updateFrame(sf::Time deltaTime)
{
    windowManager.update();

    GameContext::getPlayer()->update(deltaTime);
    bar->update();

    map->animate(deltaTime);

    help->update();

    if (verifyIfWon(*GameContext::getPlayer()))
    {
        hasPlayerWon = true;
    }
}

void GameController::render(sf::Color backgroundColor)
{
    windowManager.beginDraw();

    windowManager.switchToView("menu");
    windowManager.draw(*menu);

    windowManager.switchToView("map");
    windowManager.draw(*map);

    windowManager.switchToView("resources");
    windowManager.draw(*bar);

    windowManager.switchToView("help");
    windowManager.draw(*help);
    
    windowManager.endDraw();
}

void GameController::handleInput()
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

            if (windowManager.getViewport("menu").contains(pos))
            {
                windowManager.switchToView("menu");
                sceneCords = windowManager.mapPixelToCoords({pos.x, pos.y});
                menu->click(sceneCords.x, sceneCords.y);
            }

            if (windowManager.getViewport("map").contains({pos.x, pos.y}))
            {
                windowManager.switchToView("map");
                sceneCords = windowManager.mapPixelToCoords({pos.x, pos.y});
                map->click(sceneCords.x, sceneCords.y);
            }
        }
    }
    else
    {
        wasMouseButtonAlreadyPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (currentPressedKey == sf::Keyboard::Key::Unknown)
        {
            if (lastVerticalDirectionKey == sf::Keyboard::Up)
            {
                map->selectNeighborTile(TileMap::TileDirections::UP_LEFT);
            }
            else if (lastVerticalDirectionKey == sf::Keyboard::Down)
            {
                map->selectNeighborTile(TileMap::TileDirections::DOWN_LEFT);
            }
            currentPressedKey = sf::Keyboard::Left;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (currentPressedKey == sf::Keyboard::Key::Unknown)
        {
            if (lastVerticalDirectionKey == sf::Keyboard::Up)
            {
                map->selectNeighborTile(TileMap::TileDirections::UP_RIGHT);
            }
            else if (lastVerticalDirectionKey == sf::Keyboard::Down)
            {
                map->selectNeighborTile(TileMap::TileDirections::DOWN_RIGHT);
            }
            currentPressedKey = sf::Keyboard::Right;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (currentPressedKey == sf::Keyboard::Key::Unknown)
        {
            map->selectNeighborTile(TileMap::TileDirections::UP);
            currentPressedKey = sf::Keyboard::Up;
            lastVerticalDirectionKey = sf::Keyboard::Up;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (currentPressedKey == sf::Keyboard::Key::Unknown)
        {
            map->selectNeighborTile(TileMap::TileDirections::DOWN);
            currentPressedKey = sf::Keyboard::Down;
            lastVerticalDirectionKey = sf::Keyboard::Down;
        }
    }
    else
    {
        currentPressedKey = sf::Keyboard::Key::Unknown;
    }
}

bool GameController::verifyIfWon(Empire player)
{
    return player.getConstructionsNumber() >= 7;
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

bool GameController::isOver() { return windowManager.isDone() || hasPlayerWon; }
