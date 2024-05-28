#include "GameController.hpp"
#include "ContextMenu.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): windowManager("Dawn of Empires"), 
    wasButtonAlreadyPressed(false)
{
    windowManager.createView("map", {0, 0}, {0.8, 1});
    windowManager.createView("menu", {0.8, 0}, {0.2, 1});

    int mapRadius = 3;
    sf::Vector2f viewCenter = windowManager.getViewSize("map") * 0.5f;
    map = new TileMap(mapRadius, viewCenter);

    players.push_back(Empire());
    menu = new ActionMenu(windowManager.getViewSize("menu"));

    GameContext::setEmpire(&players[0]);
}

GameController::~GameController()
{

}

void GameController::updateFrame(sf::Time deltaTime)
{
    windowManager.update();

    map->animate(deltaTime);
}

void GameController::render(sf::Color backgroundColor)
{
    windowManager.beginDraw();

    windowManager.switchToView("menu");
    windowManager.draw(*menu);

    windowManager.switchToView("map");
    windowManager.draw(*map);

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
