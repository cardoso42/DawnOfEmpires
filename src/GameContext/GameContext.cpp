#include "GameContext.hpp"
#include <cassert>

GameContext* GameContext::sInstance = nullptr;

GameContext::GameContext()
{
    assert(sInstance == nullptr);

    sInstance = this;

    tile = nullptr;
}

void GameContext::setTile(TilePiece* newTile) { sInstance->tile = newTile; }
void GameContext::setPlayers(int playersNumber)
{
    const std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, 
        sf::Color::Black, sf::Color::Magenta, sf::Color::Cyan, sf::Color::White
    };

    if (playersNumber > colors.size())
    {
        throw std::logic_error("Too many players");
    }

    sInstance->players.clear();
    for (int i = 0; i < playersNumber; i++)
    {
        sInstance->players.push_back(Empire(colors[i]));
    }
    sInstance->currentPlayer = 0;
}

void GameContext::nextPlayer()
{
    sInstance->currentPlayer++;
    if (sInstance->currentPlayer >= sInstance->players.size())
    {
        sInstance->currentPlayer = 0;
    }
}

Empire* GameContext::getPlayer() { return &sInstance->players[sInstance->currentPlayer]; }
TilePiece *GameContext::getTile() { return sInstance->tile; }
int GameContext::getTileHrCost() { return 3; }
int GameContext::getTileImprovementHrCost() { return 1; }
