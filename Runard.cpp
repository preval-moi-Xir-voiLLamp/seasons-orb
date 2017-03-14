#include "Runard.h"
#include "Grid.h"

Runard::Runard(Grid &world, Phoenix &phoenix)
:
    Object(world, sf::Color::Yellow, sf::Vector2i(2, 2)),
    m_Phoenix(phoenix)
{
}

Runard::~Runard(void)
{
}

void Runard::impl_update(float)
{

}

void Runard::impl_nextStep(void)
{
    sf::Vector2i diff = m_Phoenix.getOldPosition() - getPosition();
    Direction toMove = Direction::None;

    if(diff.x < 0)
        toMove = Direction::Left;
    if(diff.x > 0)
        toMove = Direction::Right;
    if(diff.y < 0)
        toMove = Direction::Up;
    if(diff.y > 0)
        toMove = Direction::Down;

    move(getPosition() + toMove);
}
