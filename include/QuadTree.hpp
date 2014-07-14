#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class QuadTree
{
    friend class QuadTreeRenderer;

    public:
        QuadTree(const sf::FloatRect& bounds, int nodeCapacity);
        ~QuadTree();

        void insert(const std::vector<sf::Vector2f>& points);
        bool insert(const sf::Vector2f& point);
        void clear();

    private:
        void subdivide();

    private:
        const unsigned NODE_CAPACITY;
        std::vector<sf::Vector2f> m_Points;

        sf::FloatRect m_Bounds;

        QuadTree* m_NorthWest;
        QuadTree* m_NorthEast;
        QuadTree* m_SouthWest;
        QuadTree* m_SouthEast;
};

#endif

