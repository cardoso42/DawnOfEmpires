#include "WindowManager.hpp"
#include "GameContext.hpp"

#include <iostream>
#include <atomic>

WindowManager::WindowManager(const WindowManager &other)
{
    windowTitle = other.windowTitle;
    windowSize = other.windowSize;
    m_isFullscreen = other.m_isFullscreen;
    focus = other.focus;
    lastMousePos = other.lastMousePos;
    views = other.views;

    create();
}

WindowManager::WindowManager(const std::string &title) : focus(true)
{
    sf::VideoMode videoMode(800, 600);
    
    auto fullscreenModes = sf::VideoMode::getFullscreenModes();
    if (fullscreenModes.size() > 0)
    {
        videoMode = fullscreenModes[0];
    }

    lastMousePos = sf::Mouse::getPosition();

    setup(title, {videoMode.width, videoMode.height});
}

WindowManager::WindowManager(const std::string& l_title, const sf::Vector2u& l_size)
{
    setup(l_title, l_size);
}

void WindowManager::setup(const std::string& l_title, const sf::Vector2u& l_size)
{
    windowTitle = l_title;
    windowSize = l_size;
    m_isFullscreen =  false;
    create();
}

void WindowManager::create()
{
    auto sytle = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    sf::RenderWindow::create({windowSize.x, windowSize.y}, windowTitle, sytle);

    setFramerateLimit(60);

    m_isDone = false;
}

void WindowManager::destroy()
{
    close();
}

void WindowManager::update()
{
    sf::Event event;

    while (pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
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

        case sf::Event::MouseMoved:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                auto it = views.find("map");
                if (it == views.end())
                {
                    break;
                }

                sf::View& view = *it->second;

                sf::Vector2i currentMousePos = sf::Mouse::getPosition();
                sf::Vector2f displacement = static_cast<sf::Vector2f>(currentMousePos - lastMousePos);
                
                float zoomFactor = view.getSize().x / getSize().x;
                displacement *= zoomFactor;

                view.move(-(sf::Vector2f)(currentMousePos - lastMousePos) * zoomFactor);
                setView(view);
            } 
            lastMousePos = sf::Mouse::getPosition();
            break;

        case sf::Event::GainedFocus:
            if (!focus)
            {
                focus = true;
            }
            break;

        case sf::Event::LostFocus:
            if (focus)
            {
                GameContext::notifyEvent(GameContext::GameEvents::PAUSE);
                focus = false;
            }
            break;

        default:
            break;
        }
    }
}

void WindowManager::zoom(float delta)
{
    sf::View& view = *views["map"];
    sf::Vector2i mousePixel = sf::Mouse::getPosition();
    
    sf::Vector2f beforeZoom = mapPixelToCoords(mousePixel, view);
    view.zoom(1 - (delta * 0.1f));
    sf::Vector2f afterZoom = mapPixelToCoords(mousePixel, view);

    sf::Vector2f offset = beforeZoom - afterZoom;
    view.move(offset);

    setView(view);
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

bool WindowManager::removeView(std::string name)
{
    auto view = views.find(name);

    if (view != views.end())
    {
        delete view->second;
        views.erase(view);
        return true;
    }

    return false;
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

void WindowManager::saveCurrentViews()
{  
    for (auto& view : views)
    {
        savedViews[view.first] = view.second;
    }
    views.clear();
}

void WindowManager::restoreSavedViews()
{
    for (auto view : views)
    {
        delete view.second;
    }
    views.clear();

    for (auto view : savedViews)
    {
        views[view.first] = new sf::View(*view.second);
    }
    savedViews.clear();
}

void WindowManager::centerOnSelectedTile()
{
    auto tile = GameContext::getTile();
    if (tile == nullptr)
    {
        return;
    }

    auto it = views.find("map");
    if (it == views.end())
    {
        throw std::logic_error("Map view not found");
    }

    sf::View& view = *it->second;
    view.setCenter(tile->getPosition());
    setView(view);
}

void WindowManager::draw(sf::Drawable& l_drawable)
{
    sf::RenderWindow::draw(l_drawable);
}

bool WindowManager::isDone() { return m_isDone; }

bool WindowManager::isFullscreen() { return m_isFullscreen; }

bool WindowManager::isFocused() { return focus; }

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

sf::IntRect WindowManager::getViewport(std::string name)
{
    auto view = views.find(name);

    if (view == views.end())
    {
        throw std::invalid_argument(name + " does not exist as view");
    }

    return sf::RenderWindow::getViewport(*(view->second));
}

void WindowManager::close()
{
    m_isDone = true;
    RenderWindow::close();
}
