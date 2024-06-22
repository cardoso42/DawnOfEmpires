#include "main.hpp"

int main()
{
    XInitThreads();
    srand(time(NULL));
    
    AssetManager assetManager;
    IdGenerator idGenerator;
    GameContext context(2, 25);
    GameController game;

    sf::Clock clock;
    while (!game.isOver())
    {
        sf::Time deltaTime = clock.restart();

        game.handleInput();
        game.updateFrame(deltaTime);
        game.render();
    }
 
    return EXIT_SUCCESS;
}
