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

bool Grid::canMove(sf::Vector2i p, Direction d) const
{
    switch(d)
    {
    case Direction::None:
        return true;
    case Direction::Left:
        return p.x > 0;
    case Direction::Right:
        return p.x < m_Width - 1;
    case Direction::Up:
        return p.y > 0;
    case Direction::Down:
        return p.y < m_Height - 1;
    }

    return true;
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

