#include <iostream>
#include "Phoenix.h"
#include "Grid.h"

Phoenix::Phoenix(const Grid &world)
:
    Object(world)
{
}

Phoenix::~Phoenix(void)
{
}

void Phoenix::update(float dt)
{
    // Update regularilly
    Object::update(dt);
    return;
}

void Phoenix::nextStep(void)
{
    Direction d = Direction::None;
    sf::Vector2i p = m_Position;

    switch(m_World.currentAction())
    {
    case Action::Up:
        d = Direction::Up;
        p.y -= 1;
        break;

    case Action::Down:
        d = Direction::Down;
        p.y += 1;
        break;

    case Action::Left:
        d = Direction::Left;
        p.x -= 1;
        break;

    case Action::Right:
        d = Direction::Right;
        p.x += 1;
        break;

    default:
        break;
    }

    if(d != Direction::None
    && m_World.canMove(m_Position, d))
    {
       m_Position = p;
    }

    Object::nextStep();
}
