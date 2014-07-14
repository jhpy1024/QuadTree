#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Application
{
public:
    Application(int width, int height);
    Application(const std::string& args);

    void run();

    void handleInput();
    void update(const sf::Time& delta);
    void draw();

private:
    int m_Width;
    int m_Height;

    sf::RenderWindow m_Window;

    sf::Clock m_Clock;
};

#endif

