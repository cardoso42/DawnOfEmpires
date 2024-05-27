#include "WindowManager.hpp"
#include "ContextMenu.hpp"

#include <iostream>
#include <atomic>

WindowManager::WindowManager(const std::string& title)
{
    sf::VideoMode videoMode(800, 600);
    
    auto fullscreenModes = sf::VideoMode::getFullscreenModes();
    if (fullscreenModes.size() > 0)
    {
        videoMode = fullscreenModes[0];
    }

    setup(title, {videoMode.width, videoMode.height});
}

WindowManager::WindowManager(const std::string& l_title, const sf::Vector2u& l_size)
{
    setup(l_title, l_size);
}

WindowManager::~WindowManager()
{
    destroy();
}

void WindowManager::setup(const std::string& l_title, const sf::Vector2u& l_size)
{
    windowTitle = l_title;
    windowSize = l_size;
    m_isFullscreen =  false;
    m_isDone = false;
    create();
}

void WindowManager::create()
{
    auto sytle = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    sf::RenderWindow::create({windowSize.x, windowSize.y}, windowTitle, sytle);

    setFramerateLimit(60);
}

void WindowManager::destroy()
{
    close();
}

std::atomic<bool> stopThread(false);

void createNewWindowMenu(sf::Vector2i position)
{
    sf::RenderWindow newWindow({120, 200}, "Teste", sf::Style::None);
    newWindow.setPosition(position);

    while (newWindow.isOpen() && !stopThread.load())
    {
        ContextMenu contextMenu(sf::Vector2f(newWindow.getSize().x, newWindow.getSize().y));
        sf::Event event;

        while (newWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    newWindow.close();
                }
                break;
            case sf::Event::LostFocus:
                newWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    contextMenu.click(event.mouseButton.x, event.mouseButton.y);
                }
                break;
            }

            newWindow.clear(sf::Color::Black);
            newWindow.draw(contextMenu);
            newWindow.display();
        }
    }
}

void WindowManager::finishThread()
{
    stopThread.store(true);
    if (contextMenuThread.joinable())
    {
        contextMenuThread.join();
    }
}

void WindowManager::update()
{
    sf::Event event;

    while (pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_isDone = true;
            finishThread();
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

        case sf::Event::MouseButtonPressed:

            if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                if (!stopThread.load())
                {
                    finishThread();
                }
                stopThread.store(false);
                contextMenuThread = std::thread(createNewWindowMenu, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                finishThread();
            }

            break;

        default:
            break;
        }
    }
}

void WindowManager::zoom(float delta)
{
    views["map"]->zoom(1 + delta * 0.1);
    setView(*views["map"]);
}

void WindowManager::toggleFullscreen()
{
    m_isFullscreen = !m_isFullscreen;
    destroy();
    create();
}

void WindowManager::beginDraw()
{
    clear(sf::Color::White);
}

void WindowManager::endDraw()
{
    display();
}

bool WindowManager::createView(std::string name, sf::Vector2f pos, sf::Vector2f size)
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

bool WindowManager::switchToView(std::string name)
{
    auto view = views.find(name);
    if (view == views.end())
    {
        return false;
    }

    sf::RenderWindow::setView(*(view->second));

    return true;
}

void WindowManager::draw(sf::Drawable& l_drawable)
{
    sf::RenderWindow::draw(l_drawable);
}

bool WindowManager::isDone() { return m_isDone; }

bool WindowManager::isFullscreen() { return m_isFullscreen; }

sf::Vector2u WindowManager::getWindowSize() { return windowSize; }

sf::Vector2i WindowManager::getWindowPos() { return getPosition(); }

sf::Vector2f WindowManager::getViewSize(std::string name)
{
    auto view = views.find(name);

    if (view == views.end())
    {
        return {-1, -1};
    }

    return view->second->getSize();
}
