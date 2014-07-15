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
    , POINT_SPEED(100.f)
{

}

Application::Application(const std::string& args)
    : MOUSE_CLICK_DELAY(sf::milliseconds(200))
    , POINT_SPEED(100.f)
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
            createPointAtMouse();
    }
}

void Application::update(const sf::Time& delta)
{
    for (unsigned i = 0; i < m_Points.size(); ++i)
    {
        if (m_Points[i].x < 0 || m_Points[i].x > m_Width)
            m_PointVelocities[i].x *= -1;
        if (m_Points[i].y < 0 || m_Points[i].y > m_Height)
            m_PointVelocities[i].y *= -1;

        m_Points[i] += (m_PointVelocities[i] * POINT_SPEED * delta.asSeconds());
    }

    rebuildQuadTree();
}

void Application::draw()
{
    m_Window.clear();
    
    m_QuadTreeRenderer->draw();

    m_Window.display();
}

void Application::createPointAtMouse()
{
    for (int i = 0; i < 5; ++i)
    {
        auto point = sf::Mouse::getPosition(m_Window);
        auto angle = Utils::randomAngle();
        auto velocity = sf::Vector2f(std::cos(angle), std::sin(angle));

        m_Points.push_back((sf::Vector2f) point);
        m_PointVelocities.push_back(velocity);
    }

    rebuildQuadTree();

    m_MouseCooldownClock.restart();
}

void Application::rebuildQuadTree()
{
    m_QuadTree->clear();
    m_QuadTree->insert(m_Points);
}
