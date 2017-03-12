#include "Object.h"
#include "Grid.h"

/*** AbstractObject ***/
AbstractObject::AbstractObject(void)
:
    m_Dead(false)
{
}

AbstractObject::~AbstractObject(void)
{
}

bool AbstractObject::isDead(void) const
{
    return m_Dead;
}

void AbstractObject::die(void)
{
    m_Dead = true;
}


/*** Object ***/

Object::Object(Grid &world, sf::Vector2i position)
:
    m_World(world),
    m_Sprite(),
    m_Position(position)
{
}

Object::~Object(void)
{
}

void Object::update(float dt)
{
    impl_update(dt);

    /*Invariants*/
    m_Sprite.setPosition(m_Position);
}

void Object::nextStep(void)
{
    impl_nextStep();

    /*Invariants*/
}

void Object::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    rt.draw(m_Sprite, s);
}

void Object::move(Direction d)
{
    sf::Vector2i newPos = m_Position + d;
    if(m_World.canTake(this, newPos))
    {
        m_World.pop(this, m_Position);
        m_Position = newPos;
        m_World.push(this, m_Position);
    }
}

/*** Object::Sprite ***/

Object::Sprite::Sprite(void)
:
    m_Circle(50, 50)
{
}

Object::Sprite::~Sprite(void)
{
}

void Object::Sprite::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    rt.draw(m_Circle, s);
}

void Object::Sprite::setPosition(sf::Vector2i xy)
{
    m_Circle.setPosition(xy.x * 100, xy.y * 100);
}
