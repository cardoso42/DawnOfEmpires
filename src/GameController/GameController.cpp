#include "GameController.hpp"
#include "ContextMenu.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): windowManager("Dawn of Empires"), 
    wasButtonAlreadyPressed(false), hasPlayerWon(false)
{
    windowManager.createView("map", {0, 0}, {0.8, 0.9});
    windowManager.createView("menu", {0.8, 0}, {0.2, 0.9});
    windowManager.createView("resources", {0, 0.9}, {1, 0.1});

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
    
    windowManager.endDraw();
}

void GameController::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Basically, act only when the button is first pressed
        // This is to avoid multiple calls for this block of code,
        // for example, to avoid multiple buttons clicks

        if (!wasButtonAlreadyPressed)
        {
            wasButtonAlreadyPressed = true;
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
        wasButtonAlreadyPressed = false;
    }
}

bool GameController::verifyIfWon(Empire player)
{
    return player.getConstructionsNumber() >= 1;
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
