#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "QuadTree.hpp"
#include "QuadTreeRenderer.hpp"

#include <string>
#include <SFML/Graphics.hpp>

class Application
{
public:
    Application(int width, int height);
    Application(const std::string& args);
    ~Application();

    void run();

    void handleInput();
    void update(const sf::Time& delta);
    void draw();

private:
    int m_Width;
    int m_Height;

    sf::RenderWindow m_Window;
    sf::Clock m_Clock;

    sf::Clock m_MouseCooldownClock;
    const sf::Time MOUSE_CLICK_DELAY;

    QuadTree* m_QuadTree;
    QuadTreeRenderer* m_QuadTreeRenderer;
};

#endif

