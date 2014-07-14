#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class QuadTree
{
    friend class QuadTreeRenderer;

    public:
        QuadTree(const sf::FloatRect& bounds, int nodeCapacity);

        void insert(const std::vector<sf::Vector2i>& points);
        bool insert(const sf::Vector2i& point);
        void clear();

    private:
        void subdivide();

    private:
        const unsigned NODE_CAPACITY;
        std::vector<sf::Vector2i> m_Points;

        sf::FloatRect m_Bounds;

        QuadTree* m_NorthWest;
        QuadTree* m_NorthEast;
        QuadTree* m_SouthWest;
        QuadTree* m_SouthEast;
};

#endif

