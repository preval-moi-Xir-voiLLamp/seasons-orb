#include "Grid.h"

Grid::Grid(void)
:
    m_Width(3),
    m_Height(3),
    m_Grid(m_Width, std::vector<std::list<Object *>>(m_Height)),
    m_AllLayers(),
    m_AllCharacters(*m_AllLayers.add<Layer>()),
    m_Phoenix(*m_AllCharacters.add<Phoenix>(*this))
{
}

Grid::~Grid(void)
{
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

bool Grid::canTake(Object *, sf::Vector2i pos) const
{
    return pos.x > 0 && pos.y > 0
        && pos.x < m_Width - 1 && pos.y < m_Height - 1;
}

void Grid::pop(Object *, sf::Vector2i pos)
{
    m_Grid[pos.x][pos.y].pop_front();
}

void Grid::push(Object *obj, sf::Vector2i pos)
{
    m_Grid[pos.x][pos.y].push_front(obj);
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

