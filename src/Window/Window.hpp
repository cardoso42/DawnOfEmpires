#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Window : public sf::RenderWindow
{
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    ~Window();

    void beginDraw();
    void endDraw();

    void update();

    bool isDone();
    bool isFullscreen();
    sf::Vector2u getWindowSize();
    sf::Vector2i getWindowPos();
    
    void zoom(float delta);

    void toggleFullscreen();

    void draw(sf::Drawable& l_drawable);

private:
    void setup(const std::string& l_title, const sf::Vector2u& l_size);
    void destroy();
    void create();

    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
};

#endif // WINDOW_HPP
