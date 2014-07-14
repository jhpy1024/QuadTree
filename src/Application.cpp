#include "Application.hpp"
#include "Utils.hpp"

#include <iostream>

Application::Application(int width, int height)
    : m_Width(width)
    , m_Height(height)
    , m_Window(sf::VideoMode(width, height), "QuadTree", sf::Style::Close)
    , MOUSE_CLICK_DELAY(sf::milliseconds(50))
    , m_QuadTree(new QuadTree(sf::FloatRect(0.f, 0.f, m_Width, m_Height), 4))
    , m_QuadTreeRenderer(new QuadTreeRenderer(m_Window, m_QuadTree))
{

}

Application::Application(const std::string& args)
    : MOUSE_CLICK_DELAY(sf::milliseconds(200))
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

    m_QuadTree = new QuadTree(sf::FloatRect(0.f, 0.f, m_Width, m_Height), 4);
    m_QuadTreeRenderer = new QuadTreeRenderer(m_Window, m_QuadTree);
}

Application::~Application()
{
    delete m_QuadTree;
    delete m_QuadTreeRenderer;
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

    if (m_MouseCooldownClock.getElapsedTime() >= MOUSE_CLICK_DELAY)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            auto point = sf::Mouse::getPosition(m_Window);
            m_QuadTree->insert(point);

            m_MouseCooldownClock.restart();
        }
    }
}

void Application::update(const sf::Time& delta)
{

}

void Application::draw()
{
    m_Window.clear();
    
    m_QuadTreeRenderer->draw();

    m_Window.display();
}
