#include <iostream>
#include "Grid.h"

/*! \brief Default constructor for the Grid.
 *
 * This is the initialisation of the game. It creates its own object manager so
 * as to have more control on their update cycle.
 */
Grid::Grid():
    m_Width(3),
    m_Height(3),
    m_Grid(m_Width, std::vector<std::list<Object *>>(m_Height)),
    m_AllLayers(),
    m_AllCharacters(*m_AllLayers.add<Layer>()),
    m_Phoenix(*m_AllCharacters.add<Phoenix>(*this))
{
}

Grid::~Grid()
{
}

Action Grid::currentAction(void) const
{
    return m_Action;
}

void Grid::act(Action a)
{
    m_Action = a;
    nextStep();
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

