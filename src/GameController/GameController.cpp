#include "GameController.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): window("Dawn of Empires")
{
    window.createView("map", {0, 0}, {0.8, 1});
    window.createView("menu", {0.8, 0}, {0.2, 1});

    int mapRadius = 2;
    sf::Vector2f viewCenter = window.getViewSize("map") * 0.5f;
    map = new TileMap(mapRadius, viewCenter);

    menu = new ActionMenu(window.getViewSize("menu"));

    players.push_back(Empire());

    // setar listener
}

GameController::~GameController()
{

}

void GameController::updateFrame(sf::Time deltaTime)
{
    window.update();

    map->animate(deltaTime);
}

void GameController::render(sf::Color backgroundColor)
{
    window.beginDraw();

    window.switchToView("menu");
    window.draw(*menu);

    window.switchToView("map");
    window.draw(*map);

    window.endDraw();
}

void GameController::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        map->click(pos.x, pos.y);
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

bool GameController::isOver() { return window.isDone(); }
