/*! \file Object.h */
#ifndef HEAD_OBJECT
#define HEAD_OBJECT
#include <SFML/Graphics.hpp>

/*! \brief Type of every objects in our game
 *
 * This is the general type of every objects we will ever use. It defines the
 * function that one needs to implement and that will be called for every one of
 * them.
 * The two function to be implemented are draw and update.
 */
class AbstractObject: public sf::Drawable
{
public:
    AbstractObject(void);
    virtual ~AbstractObject(void);
    virtual void update(float dt) = 0;
    virtual void nextStep(void) = 0;
    bool isDead(void);
    
protected:
    void die(void);

private:
    bool m_Dead; /*!< Is the object to be destroyed */
};

class Grid;
/*! \brief Type of every object that are killable or directly in game (e.g not HUB or particule
 * effects).
 *
 * Such objects all have a sprite, and can die by setting their m_Dead flag to
 * true in the update function (the ObjectManager will take care of deleting
 * them)
 */
class Object: public AbstractObject
{
public:
    Object(const Grid &world, sf::Vector2i position=sf::Vector2i(0, 0));
    virtual ~Object(void);
    void update(float dt) override = 0;
    void nextStep(void) override = 0;
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;

protected:
    const Grid &m_World; /*!< The world the object lives in*/
    sf::Vector2i m_Position; /*!< The current position of the object*/

private:
    /*! \brief The sprite to draw the object
     *
     * A circle for now
     */
    struct Sprite: public sf::Drawable
    {
        Sprite();
        virtual ~Sprite();
        void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;
        void setPosition(sf::Vector2i v);

        sf::CircleShape m_Circle; /*!< The content of the sprite*/
    } m_Sprite;
};

#endif //HEAD_OBJECT
