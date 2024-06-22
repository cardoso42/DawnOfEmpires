#include "GameContext.hpp"
#include <cassert>

GameContext* GameContext::sInstance = nullptr;

const std::vector<sf::Color> GameContext::colors ={
    sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, 
    sf::Color::Black, sf::Color::Magenta, sf::Color::Cyan, sf::Color::White
};

GameContext::GameContext(int numPlayers, int mapSize) : tile(nullptr), mapSize(mapSize),
    windowManager("Dawn of Empires"), currentPlayer(0), playersNumber(numPlayers)
{
    assert(sInstance == nullptr);
    sInstance = this;
}

void GameContext::startGame() 
{
    setPlayers(sInstance->playersNumber);
    sInstance->events.push_back(GAME_STARTED); 
    sInstance->tile = nullptr;
}

void GameContext::setNumPlayers(int numPlayers)
{
    sInstance->playersNumber = numPlayers;
}

void GameContext::setTile(TilePiece *newTile) { sInstance->tile = newTile; }

void GameContext::setMapSize(int size) { sInstance->mapSize = size; }

void GameContext::setPlayers(int playersNumber)
{
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
    getPlayer()->setLastSelectedTile(getTile());

    sInstance->currentPlayer++;
    if (sInstance->currentPlayer >= sInstance->players.size())
    {
        sInstance->currentPlayer = 0;
    }

    if (getPlayer()->haveWon())
    {
        sInstance->events.push_back(GAME_OVER);
        return;
    }

    sInstance->events.push_back(NEXT_TURN);
}

void GameContext::playSound(sf::SoundBuffer &buffer)
{
    if (sInstance->soundEffect.getStatus() == sf::Sound::Playing)
    {
        sInstance->soundEffect.stop();
    }

    sInstance->soundEffect.setBuffer(buffer);
    sInstance->soundEffect.play();
}

void GameContext::notifyEvent(GameEvents event)
{
    sInstance->events.push_back(event);
}

Empire* GameContext::getPlayer() { return &sInstance->players[sInstance->currentPlayer]; }
TilePiece *GameContext::getTile() { return sInstance->tile; }
int GameContext::getTileHrCost() { return 3; }

std::vector<GameContext::GameEvents> GameContext::getEvents()
{
    auto events = sInstance->events;
    sInstance->events.clear();
    return events;
}

int GameContext::getMapSize() { return sInstance->mapSize; }

WindowManager &GameContext::getWindowManager() { return sInstance->windowManager; }

int GameContext::getPlayersNumber() { return sInstance->playersNumber; }

int GameContext::getMaxPlayersNumber() { return colors.size(); }

int GameContext::getMaxMapSize() { return 50; }

void GameContext::verifyIfPlayerWon()
{
    auto empire = getPlayer();

    if (empire->getConstructionsNumber() >= 7)
    {
        empire->setAsWinner();
    }
}
