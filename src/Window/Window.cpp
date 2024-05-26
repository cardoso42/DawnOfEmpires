#include "Window.hpp"

Window::Window()
{
    setup("Window", {640, 480});
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
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen =  false;
    m_isDone = false;
    create();
}

void Window::create()
{
    auto sytle = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    sf::RenderWindow::create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, sytle);
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
    sf::View view = getView();
    view.zoom(1 + delta * 0.1);
    setView(view);
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

bool Window::isDone() { return m_isDone; }

bool Window::isFullscreen() { return m_isFullscreen; }

sf::Vector2u Window::getWindowSize() { return m_windowSize; }

void Window::draw(sf::Drawable& l_drawable)
{
    sf::RenderWindow::draw(l_drawable);
}

sf::Vector2i Window::getWindowPos() { return getPosition(); }
