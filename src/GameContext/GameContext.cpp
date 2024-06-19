#include "GameContext.hpp"
#include <cassert>

GameContext* GameContext::sInstance = nullptr;

GameContext::GameContext() : gameOver(false), tile(nullptr)
{
    assert(sInstance == nullptr);
    sInstance = this;
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
    verifyIfPlayerWon();

    sInstance->currentPlayer++;
    if (sInstance->currentPlayer >= sInstance->players.size())
    {
        sInstance->currentPlayer = 0;
    }

    if (getPlayer()->haveWon())
    {
        sInstance->gameOver = true;
    }
}

bool GameContext::isGameOver() { return sInstance->gameOver; }

Empire* GameContext::getPlayer() { return &sInstance->players[sInstance->currentPlayer]; }
TilePiece *GameContext::getTile() { return sInstance->tile; }
int GameContext::getTileHrCost() { return 3; }

bool GameContext::verifyIfPlayerWon()
{
    auto empire = getPlayer();

    if (empire->getConstructionsNumber() > 7)
    {
        empire->setAsWinner();
    }
}
