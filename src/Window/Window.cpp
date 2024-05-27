#include "Window.hpp"

#include <iostream>

Window::Window(const std::string& title)
{
    sf::VideoMode videoMode(800, 600);
    
    auto fullscreenModes = sf::VideoMode::getFullscreenModes();
    if (fullscreenModes.size() > 0)
    {
        videoMode = fullscreenModes[0];
    }

    setup(title, {videoMode.width, videoMode.height});
}

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
    setup(l_title, l_size);
}

Window::~Window()
{
    destroy();
}

void Window::setup(const std::string& l_title, const sf::Vector2u& l_size)
{
    windowTitle = l_title;
    windowSize = l_size;
    m_isFullscreen =  false;
    m_isDone = false;
    create();
}

void Window::create()
{
    auto sytle = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    sf::RenderWindow::create({windowSize.x, windowSize.y}, windowTitle, sytle);

    setFramerateLimit(60);
}

void Window::destroy()
{
    close();
}

void Window::update()
{
    sf::Event event;

    while (pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_isDone = true;
            close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::F5)
            {
                toggleFullscreen();
            }
            break;
        
        case sf::Event::MouseWheelScrolled:
            zoom(event.mouseWheelScroll.delta);
            break;
        
        default:
            break;
        }
    }
}

void Window::zoom(float delta)
{
    views["map"]->zoom(1 + delta * 0.1);
    setView(*views["map"]);
}

void Window::toggleFullscreen()
{
    m_isFullscreen = !m_isFullscreen;
    destroy();
    create();
}

void Window::beginDraw()
{
    clear(sf::Color::White);
}

void Window::endDraw()
{
    display();
}

bool Window::createView(std::string name, sf::Vector2f pos, sf::Vector2f size)
{
    if (views.find(name) != views.end())
    {
        return false;
    }

    const float width = windowSize.x * size.x;
    const float height = windowSize.y * size.y;

    views[name] = new sf::View({0, 0, width, height});
    views[name]->setViewport({pos.x, pos.y, size.x, size.y});
    
    return true;
}

bool Window::switchToView(std::string name)
{
    auto view = views.find(name);
    if (view == views.end())
    {
        return false;
    }

    sf::RenderWindow::setView(*(view->second));

    return true;
}

void Window::draw(sf::Drawable& l_drawable)
{
    sf::RenderWindow::draw(l_drawable);
}

bool Window::isDone() { return m_isDone; }

bool Window::isFullscreen() { return m_isFullscreen; }

sf::Vector2u Window::getWindowSize() { return windowSize; }

sf::Vector2i Window::getWindowPos() { return getPosition(); }

sf::Vector2f Window::getViewSize(std::string name)
{
    auto view = views.find(name);

    if (view == views.end())
    {
        return {-1, -1};
    }

    return view->second->getSize();
}
