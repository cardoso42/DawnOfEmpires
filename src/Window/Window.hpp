#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Window : public sf::RenderWindow
{
public:
    Window(const std::string& title);
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();

    bool createView(std::string name, sf::Vector2f pos, sf::Vector2f size);
    bool switchToView(std::string name);
    void beginDraw();
    void endDraw();
    void update();

    bool isDone();
    bool isFullscreen();

    sf::Vector2u getWindowSize();
    sf::Vector2i getWindowPos();
    sf::Vector2f getViewSize(std::string name);

    void draw(sf::Drawable& drawable);

private:
    void setup(const std::string& title, const sf::Vector2u& size);
    void destroy();
    void create();
    void zoom(float delta);
    void toggleFullscreen();

    sf::Vector2u windowSize;
    std::string windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
    std::map<std::string, sf::View*> views;
};

#endif // WINDOW_HPP
