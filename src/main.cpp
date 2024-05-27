#include "main.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>
#include "IdGenerator.hpp"
#include <X11/Xlib.h>

int main()
{
    XInitThreads();
    
    AssetManager assetManager;
    IdGenerator idGenerator;
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
