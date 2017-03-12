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

void AbstractObject::nextStep(void)
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

Object::Object(const Grid &world, sf::Vector2i position)
:
    m_World(world),
    m_Position(position),
    m_Sprite()
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
