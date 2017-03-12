#include "Phoenix.h"
#include "Grid.h"

Phoenix::Phoenix(Grid &world)
:
    Object(world)
{
}

Phoenix::~Phoenix(void)
{
}

void Phoenix::impl_update(float)
{
    return;
}

void Phoenix::impl_nextStep(void)
{
    Direction d = Direction::None;

    /*! \todo Have a conversion from Action to direction */
    switch(m_World.currentAction())
    {
    case Action::Up:
        d = Direction::Up;
        break;

    case Action::Down:
        d = Direction::Down;
        break;

    case Action::Left:
        d = Direction::Left;
        break;

    case Action::Right:
        d = Direction::Right;
        break;

    default:
        break;
    }

    if(d != Direction::None)
    {
        move(d);
    }
}
