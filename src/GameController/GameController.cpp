#include "GameController.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(int id, sf::Vector2u windowSize, sf::FloatRect viewport) : gameId(id)
{
    view = sf::View(
        sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f),
        sf::Vector2f(windowSize.x, windowSize.y)
    );
    view.setViewport(viewport);

    map = new TileMap(2, {windowSize.x * 0.5f, windowSize.y * 0.5f});

    // setar listener
}

void GameController::updateFrame(sf::Time deltaTime)
{
    map->animate(deltaTime);
}

void GameController::drawOn(sf::RenderWindow& window, sf::Color backgroundColor)
{
    map->drawOn(window);
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

sf::View GameController::getView()
{
    return view;
}

int GameController::getId()
{
    return gameId;
}
