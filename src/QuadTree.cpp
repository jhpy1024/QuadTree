#include "QuadTree.hpp"

QuadTree::QuadTree(const sf::FloatRect& bounds, int nodeCapacity)
    : NODE_CAPACITY(nodeCapacity)
    , m_Bounds(bounds)
    , m_NorthWest(nullptr)
    , m_NorthEast(nullptr)
    , m_SouthWest(nullptr)
    , m_SouthEast(nullptr)
{

}

QuadTree::~QuadTree()
{
    delete m_NorthWest;
    delete m_NorthEast;
    delete m_SouthWest;
    delete m_SouthEast;
}

void QuadTree::insert(const std::vector<sf::Vector2f>& points)
{
    for (auto& point : points)
        insert(point);
}

bool QuadTree::insert(const sf::Vector2f& point)
{
    // The point is not within the bounds of this node so 
    // should not be added to this node
    if (!m_Bounds.contains(sf::Vector2f(point.x, point.y)))
        return false;

    // If the point will fit in this node then add it
    if (m_Points.size() < NODE_CAPACITY)
    {
        m_Points.push_back(point);
        return true;
    }

    // The point cannot be added to this node so subdivide
    // into 4 more nodes and then try to add the point
    // to any of those 4 nodes
    if (m_NorthWest == nullptr)
        subdivide();

    if (m_NorthWest->insert(point)) return true;
    if (m_NorthEast->insert(point)) return true;
    if (m_SouthWest->insert(point)) return true;
    if (m_SouthEast->insert(point)) return true;

    // The point could not be inserted anywhere. This should
    // never happen.
    return false;
}

void QuadTree::clear()
{
    m_Points.clear();

    delete m_NorthWest;
    delete m_NorthEast;
    delete m_SouthWest;
    delete m_SouthEast;

    m_NorthWest = nullptr;
    m_NorthEast = nullptr;
    m_SouthWest = nullptr;
    m_SouthEast = nullptr;
}

void QuadTree::subdivide()
{
    sf::FloatRect northWestBounds(m_Bounds.left, m_Bounds.top, m_Bounds.width / 2.f, m_Bounds.height / 2.f);
    sf::FloatRect northEastBounds(m_Bounds.left + m_Bounds.width / 2.f, m_Bounds.top, m_Bounds.width / 2.f, m_Bounds.height / 2.f);
    sf::FloatRect southWestBounds(m_Bounds.left, m_Bounds.top + m_Bounds.height / 2.f, m_Bounds.width / 2.f, m_Bounds.height / 2.f);
    sf::FloatRect southEastBounds(m_Bounds.left + m_Bounds.width / 2.f, m_Bounds.top + m_Bounds.height / 2.f, m_Bounds.width / 2.f, m_Bounds.height / 2.f);

    m_NorthWest = new QuadTree(northWestBounds, NODE_CAPACITY);
    m_NorthEast = new QuadTree(northEastBounds, NODE_CAPACITY);
    m_SouthWest = new QuadTree(southWestBounds, NODE_CAPACITY);
    m_SouthEast = new QuadTree(southEastBounds, NODE_CAPACITY);
}
