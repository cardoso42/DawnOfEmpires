#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <thread>

class WindowManager : public sf::RenderWindow
{
public:
    WindowManager(const std::string& title);
    WindowManager(const std::string& title, const sf::Vector2u& size);
    ~WindowManager();

    bool createView(std::string name, sf::Vector2f pos, sf::Vector2f size);
    bool switchToView(std::string name);
    void beginDraw();
    void endDraw();
    void update();

    bool isDone();
    bool isFullscreen();
    bool isFocused();

    sf::Vector2u getWindowSize();
    sf::Vector2i getWindowPos();
    sf::Vector2f getViewSize(std::string name);
    sf::IntRect getViewport(std::string name);

    void draw(sf::Drawable& drawable);

private:
    void setup(const std::string& title, const sf::Vector2u& size);
    void destroy();
    void create();
    void zoom(float delta);
    void toggleFullscreen();
    void finishThread();

    sf::Vector2u windowSize;
    std::string windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
    std::map<std::string, sf::View*> views;
    std::thread contextMenuThread;
    bool focus;

    sf::Vector2i lastMousePos;
};

#endif // WINDOW_HPP
