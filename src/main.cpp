#include "main.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>

const sf::Color backgroundColor = sf::Color::Black;

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

void updateFrame(GameController &game)
{
}
 
void renderFrame(sf::RenderWindow &window, GameController game)
{
    window.clear(backgroundColor);

    // render other objects

    window.display();
}

int main()
{
    AssetManager assetManager;

    sf::RenderWindow window;
    createWindow(window);

    int gameId{0};
    sf::FloatRect viewport = {0, 0, 1, 1};
    GameController game(++gameId, window.getSize(), viewport);

    while (window.isOpen())
    {
        handleInput(window);
        updateFrame(game);
        renderFrame(window, game);
    }
 
    return EXIT_SUCCESS;
}
