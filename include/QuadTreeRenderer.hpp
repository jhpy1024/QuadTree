#ifndef QUAD_TREE_RENDERER_HPP
#define QUAD_TREE_RENDERER_HPP

#include "QuadTree.hpp"

#include <SFML/Graphics.hpp>

class QuadTreeRenderer
{
    public:
        QuadTreeRenderer(sf::RenderWindow& window, QuadTree* quadTree);

        void draw();

        void setQuadColor(const sf::Color& color);
        void setQuadOutlineColor(const sf::Color& color);
        void setPointColor(const sf::Color& color);
        void setPointRadius(float radius);
        void setQuadOutlineThickness(float thickness);

    private:
        void draw(QuadTree* node);
        void drawQuad(QuadTree* node);
        void drawPoints(QuadTree* node);

    private:
        sf::RenderWindow& m_Window;

        QuadTree* m_QuadTree;

        sf::Color m_QuadColor;
        sf::Color m_QuadOutlineColor;
        sf::Color m_PointColor;
        float m_PointRadius;
        float m_QuadOutlineThickness;
};

#endif
