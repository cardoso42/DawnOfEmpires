#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <thread>

class WindowManager : public sf::RenderWindow
{
public:
    WindowManager(const WindowManager& other);
    WindowManager(const std::string& title);
    WindowManager(const std::string& title, const sf::Vector2u& size);

    bool createView(std::string name, sf::Vector2f pos, sf::Vector2f size);
    bool removeView(std::string name);
    bool switchToView(std::string name);
    void saveCurrentViews();
    void restoreSavedViews();
    void centerOnSelectedTile();
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

    void close() override;

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
    bool focus;
    std::map<std::string, sf::View*> views;
    std::map<std::string, sf::View*> savedViews;

    sf::Vector2i lastMousePos;
};

#endif // WINDOW_HPP
