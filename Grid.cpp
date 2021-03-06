#include "Grid.h"

Grid::Grid(void)
:
    m_Width(3),
    m_Height(3),
    m_Grid(m_Width, std::vector<std::list<Object *>>(m_Height)),
    m_AllLayers(),
    m_AllCharacters(*m_AllLayers.add<Layer>()),
    m_Phoenix(*m_AllCharacters.add<Phoenix>(*this)),
    m_AllRunards(*m_AllCharacters.add<RunardLayer>()),
    m_Action(Action::None)
{
    m_AllRunards.add<Runard>(*this, m_Phoenix);
}

Grid::~Grid(void)
{
}

bool Grid::canTake(Object *, sf::Vector2i pos) const
{
    /*! \todo Have canTake ask for the other objects if they can take obj
     */
    return pos.x >= 0 && pos.y >= 0
        && pos.x < m_Width && pos.y < m_Height
        && m_Grid[pos.x][pos.y].empty();
}

void Grid::act(Action a)
{
    m_Action = a;
    nextStep();
    m_Action = Action::None;
}

Action Grid::currentAction(void) const
{
    return m_Action;
}

void Grid::correct(Object *obj)
{
    sf::Vector2i oldPos = obj->getOldPosition();
    sf::Vector2i newPos = obj->getPosition();

    m_Grid[oldPos.x][oldPos.y].remove(obj);

    /*! \todo Have the grid asks for the object to accept the new one*/
    m_Grid[newPos.x][newPos.y].push_front(obj);
}

void Grid::update(float dt)
{
    m_AllLayers.update(dt);
}

void Grid::nextStep(void)
{
    m_AllLayers.nextStep();
}

void Grid::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    m_AllLayers.draw(rt, s);
}

