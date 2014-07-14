#include "Application.hpp"
#include "Utils.hpp"

#include <iostream>

Application::Application(int width, int height)
    : m_Width(width)
    , m_Height(height)
    , m_Window(sf::VideoMode(width, height), "QuadTree", sf::Style::Close)
{

}

Application::Application(const std::string& args)
{
    int defaultWidth = 500;
    int defaultHeight = 500;

    auto splitArgs = Utils::splitString(args, ' ');
    if (splitArgs.size() != 2)
    {
        std::cerr << "Usage: <width> <height>" << std::endl
                  << "Using default arguments" << std::endl;
        m_Width = defaultWidth;
        m_Height = defaultHeight;
    }
    else
    {
        m_Width = Utils::stringToInt(splitArgs[0], defaultWidth);
        m_Height = Utils::stringToInt(splitArgs[1], defaultHeight);
    }

    m_Window.create(sf::VideoMode(m_Width, m_Height), "QuadTree", sf::Style::Close);
}

void Application::run()
{
    while (m_Window.isOpen())
    {
        auto deltaTime = m_Clock.restart();

        handleInput();
        update(deltaTime);
        draw();
    }
}

void Application::handleInput()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_Window.close();
                break;
            default:
                break;
        }
    }
}

void Application::update(const sf::Time& delta)
{

}

void Application::draw()
{
    m_Window.clear();

    m_Window.display();
}
