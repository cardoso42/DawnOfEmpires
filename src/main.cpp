#include "main.hpp"

int main()
{
    XInitThreads();
    
    AssetManager assetManager;
    IdGenerator idGenerator;
    GameContext context;
    GameController game;

    sf::Clock clock;
    while (!game.isOver())
    {
        sf::Time deltaTime = clock.restart();

        game.handleInput();
        game.updateFrame(deltaTime);
        game.render();
    }

#ifdef DEBUG
    game.showPlayerTerritory();
#endif
 
    return EXIT_SUCCESS;
}
