/*! \file Object.cpp
 */
#include "Object.h"
#include "Grid.h"
#include <iostream>

/*** AbstractObject ***/

/*! \brief Constructor of AbstractObject
 */
AbstractObject::AbstractObject(void)
:
    m_Dead(false)
{
}

/*! \brief Destructor of AbstractObject
 */
AbstractObject::~AbstractObject(void)
{
}

/*! \brief Updates the object
 *
 * This is a very generic function, it should be called everytime beetwen two
 * frames. The way the object will be updated depend on said objects
 */
void AbstractObject::update(
        float
        /*!< The elapsed time since last update*/)
{
}

/*! \brief Indicates wether this object will be removed next frame
 */
bool AbstractObject::isDead(void)
{
    return m_Dead;
}

/*! \brief Destroy the object next frame
 */
void AbstractObject::die(void)
{
    m_Dead = true;
}


/*** Object ***/

/*! \brief Constructor of Object
 */
Object::Object(
    const Grid &world /*!< Reference to the world the objects live in*/,
    sf::Vector2i position /*!< The starting position of the object*/)
:
    m_World(world),
    m_Position(position),
    m_Sprite()
{
}

/*! \brief Destructor of Object
 */
Object::~Object(void)
{
}

/*! \brief Updates the object
 *
 * This function shall be called by every child after their own update calls to
 * manage internal settings such as the sprite
 */
void Object::update(
    float
    /*!< Elapsed time since last update*/)
{
    m_Sprite.setPosition(m_Position);
}

void Object::nextStep(void)
{
    std::cerr << "nextStep is not implemented" << std::endl;
}

/* */
void Object::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    rt.draw(m_Sprite, s);
}

/*** Object::Sprite ***/

/*! \brief Constructor of Sprite
 */
Object::Sprite::Sprite()
:
    m_Circle(50, 50)
{
}

/*! \brief Destructor of Sprite
 */
Object::Sprite::~Sprite()
{
}

/* */
void Object::Sprite::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    rt.draw(m_Circle, s);
}

/*! \brief Set the position of the sprite
 *
 * As all positions in the world will be in their own coordinates and
 * not in pixel coordinates, we need a function to translate between the two.
 */
void Object::Sprite::setPosition(
        sf::Vector2i xy
        /*!< The position to set the sprite to*/)
{
    m_Circle.setPosition(xy.x * 100, xy.y * 100);
}
