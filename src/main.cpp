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

void handleInput(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::EventType::Closed:
            window.close();
            break;

        default:
            break;
        }
    }
}

void updateFrame(GameController &game, sf::Time deltaTime)
{
    game.updateFrame(deltaTime);
}
 
void renderFrame(sf::RenderWindow &window, GameController &game)
{
    window.clear(backgroundColor);

    game.drawOn(window);

    window.display();
}

int main()
{
    AssetManager assetManager;
    IdGenerator idGenerator;

    sf::RenderWindow window;
    createWindow(window);

    int gameId{0};
    sf::FloatRect viewport = {0, 0, 1, 1};
    GameController game(++gameId, window.getSize(), viewport);
    // window.setPosition({0,0});

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        handleInput(window);
        updateFrame(game, deltaTime);
        renderFrame(window, game);
    }
 
    return EXIT_SUCCESS;
}
