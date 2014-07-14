#include "QuadTreeRenderer.hpp"

QuadTreeRenderer::QuadTreeRenderer(sf::RenderWindow& window, QuadTree* quadTree)
    : m_Window(window)
    , m_QuadTree(quadTree)
    , m_QuadColor(4, 130, 219)
    , m_QuadOutlineColor(sf::Color::Black)
    , m_PointColor(219, 93, 4)
    , m_PointRadius(3.f)
    , m_QuadOutlineThickness(2.f)
{

}

void QuadTreeRenderer::draw()
{
    draw(m_QuadTree);    
}

void QuadTreeRenderer::setQuadColor(const sf::Color& color)
{
    m_QuadColor = color;
}

void QuadTreeRenderer::setQuadOutlineColor(const sf::Color& color)
{
    m_QuadOutlineColor = color;
}

void QuadTreeRenderer::setPointColor(const sf::Color& color)
{
    m_PointColor = color;
}

void QuadTreeRenderer::setPointRadius(float radius)
{
    m_PointRadius = radius;
}

void QuadTreeRenderer::setQuadOutlineThickness(float thickness)
{
    m_QuadOutlineThickness = thickness;
}

void QuadTreeRenderer::draw(QuadTree* node)
{
    if (node == nullptr)
        return;

    drawQuad(node);

    draw(node->m_NorthWest);
    draw(node->m_NorthEast);
    draw(node->m_SouthWest);
    draw(node->m_SouthEast);

    // We draw the points after drawing the quads so that
    // they don't get covered up by the quads
    drawPoints(node);
}

void QuadTreeRenderer::drawQuad(QuadTree* node)
{
    sf::RectangleShape quad;
    quad.setPosition(node->m_Bounds.left, node->m_Bounds.top);
    quad.setSize(sf::Vector2f(node->m_Bounds.width, node->m_Bounds.height));
    quad.setFillColor(m_QuadColor);
    quad.setOutlineColor(m_QuadOutlineColor);
    quad.setOutlineThickness(m_QuadOutlineThickness);
    m_Window.draw(quad);
}

void QuadTreeRenderer::drawPoints(QuadTree* node)
{
    sf::CircleShape pointShape;
    pointShape.setRadius(m_PointRadius);
    pointShape.setFillColor(m_PointColor);
    for (auto& point : node->m_Points)
    {
        pointShape.setOrigin(pointShape.getLocalBounds().left + pointShape.getLocalBounds().width / 2.f, pointShape.getLocalBounds().top + pointShape.getLocalBounds().height / 2.f);
        pointShape.setPosition(point.x, point.y);
        m_Window.draw(pointShape);
    }
}
