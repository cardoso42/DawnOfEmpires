#include "main.h"

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

void updateFrame()
{
}
 
void renderFrame(sf::RenderWindow &window)
{
    window.clear(backgroundColor);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    while (window.isOpen())
    {
        handleInput(window);
        updateFrame();
        renderFrame(window);
    }
 
    return EXIT_SUCCESS;
}
