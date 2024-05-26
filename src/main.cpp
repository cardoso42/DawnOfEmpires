#include "main.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>
#include "IdGenerator.hpp"

const sf::Color backgroundColor = sf::Color::White;

void createWindow(sf::RenderWindow &window)
{
    sf::VideoMode videoMode(800, 600);
    
    sf::Uint32 styles = sf::Style::Default;

    std::vector<sf::VideoMode> fullscreenModes= sf::VideoMode::getFullscreenModes();
    if (fullscreenModes.size() > 0)
    {
        videoMode = fullscreenModes[0];
        // styles = sf::Style::Fullscreen;
    }

    window.create(videoMode, "Dawn of Empires", styles);
    window.setFramerateLimit(60);
}

int main()
{
    AssetManager assetManager;
    IdGenerator idGenerator;

    GameController game;
    // window.setPosition({0,0});

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
