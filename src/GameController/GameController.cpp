#include "GameController.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): window("Dawn of Empires", {800, 600})
{
    sf::Vector2u windowSize = window.GetWindowSize();

    map = new TileMap(2, {windowSize.x * 0.5f, windowSize.y * 0.5f});

    // setar listener
}

GameController::~GameController()
{

}

void GameController::updateFrame(sf::Time deltaTime)
{
    window.Update();

    map->animate(deltaTime);
}

void GameController::render(sf::Color backgroundColor)
{
    window.BeginDraw();
    window.Draw(*map);
    window.EndDraw();
}

void GameController::handleInput()
{

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

bool GameController::isOver() { return window.IsDone(); }
