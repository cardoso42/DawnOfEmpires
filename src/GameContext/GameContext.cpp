#include "GameContext.hpp"
#include <cassert>

GameContext* GameContext::sInstance = nullptr;

const std::vector<sf::Color> GameContext::colors ={
    sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, 
    sf::Color::Black, sf::Color::Magenta, sf::Color::Cyan, sf::Color::White
};

GameContext::GameContext(int numPlayers, int mapSize) : tile(nullptr), mapSize(mapSize),
    windowManager("Dawn of Empires"), currentPlayer(0), playersNumber(numPlayers),
    musicVolume(100), sfxVolume(100)
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

void GameContext::setMusicVolume(int volume)
{
    sInstance->musicVolume = volume;
}

void GameContext::setSfxVolume(int volume)
{
    sInstance->sfxVolume = volume;
    sInstance->soundEffect.setVolume(volume);
}

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

void GameContext::addKeyAction(sf::Keyboard::Key key, CallbackFunction action)
{
    sInstance->keyActions[key] = action;
}

void GameContext::removeKeyAction(sf::Keyboard::Key key)
{
    sInstance->keyActions.erase(key);
}

void GameContext::clearKeyActions()
{
    sInstance->keyActions.clear();
}

void GameContext::clearAlphanumericKeyActions()
{
    for (auto it = sInstance->keyActions.begin(); it != sInstance->keyActions.end();)
    {
        if (it->first >= sf::Keyboard::A && it->first <= sf::Keyboard::Z)
        {
            it = sInstance->keyActions.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameContext::clearDirectionalKeyActions()
{
    for (auto it = sInstance->keyActions.begin(); it != sInstance->keyActions.end();)
    {
        if (it->first >= sf::Keyboard::Up && it->first <= sf::Keyboard::Right)
        {
            it = sInstance->keyActions.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameContext::notifyEvent(GameEvents event)
{
    sInstance->events.push_back(event);
}

Empire* GameContext::getPlayer() { return &sInstance->players[sInstance->currentPlayer]; }
Empire GameContext::getWinnerPlayer()
{
    for (auto &player : sInstance->players)
    {
        if (player.haveWon())
        {
            return player;
        }
    }

    // Decides the winner based on the number of constructions
    int maxConstructions = 0;
    int empireIndex = 0;
    bool isUnique = true;

    for (int i = 0; i < sInstance->players.size(); i++)
    {
        auto player = sInstance->players[i];
        if (player.getConstructionsNumber() > maxConstructions)
        {
            maxConstructions = player.getConstructionsNumber();
            empireIndex = i;
            isUnique = true;
        }
        else if (player.getConstructionsNumber() == maxConstructions)
        {
            isUnique = false;
        }
    }

    if (isUnique)
    {
        return sInstance->players[empireIndex];
    }

    // Decides the winner based on the number of resources
    int maxResources = 0;
    empireIndex = 0;

    for (int i = 0; i < sInstance->players.size(); i++)
    {
        auto player = sInstance->players[i];
        auto resources = player.getResources();
        
        int resourcesNumber = 0;
        for (auto resource : resources)
        {
            resourcesNumber += resource.getAmount();
        }

        if (resourcesNumber > maxResources)
        {
            maxResources = resourcesNumber;
            empireIndex = i;
        }
    }

    return sInstance->players[empireIndex];

}
TilePiece *GameContext::getTile() { return sInstance->tile; }
int GameContext::getTileHrCost() { return 3; }

std::vector<GameContext::GameEvents> GameContext::getEvents()
{
    auto events = sInstance->events;
    sInstance->events.clear();
    return events;
}

int GameContext::getMapSize() { return sInstance->mapSize; }

WindowManager *GameContext::getWindowManager() { return &sInstance->windowManager; }

int GameContext::getPlayersNumber() { return sInstance->playersNumber; }

int GameContext::getMaxPlayersNumber() { return colors.size(); }

int GameContext::getMaxMapSize() { return 50; }

int GameContext::getMusicVolume()
{
    return sInstance->musicVolume;
}

int GameContext::getSfxVolume()
{
    return sInstance->sfxVolume;
}

std::unordered_map<sf::Keyboard::Key, CallbackFunction> GameContext::getKeyActions()
{
    return sInstance->keyActions;
}

void GameContext::verifyIfPlayerWon()
{
    auto empire = getPlayer();

    if (empire->getConstructionsNumber() >= 7)
    {
        empire->setAsWinner();
    }
}
