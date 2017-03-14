/*! \file Object.h */
#ifndef HEAD_OBJECT
#define HEAD_OBJECT
#include <SFML/Graphics.hpp>
#include "Constant.h"
class Grid;

/*! \brief Type of every objects in our game
 *
 * This is the general type of every objects we will ever use.
 * This includes game object such as characters or terrain, but more obscure
 * abstraction such as grid or ObjectManager.
 * Basically, everything that needs to be drawn and updated.
 * Note that one shouldn't create any instance of AbstractObject themselve,
 * except for ObjectManagers, but instead call ObjectManager::add that takes
 * care of updating and deleting it properly.
 */
class AbstractObject: public sf::Drawable
{
public:
    /*! \brief Constructor of AbstractObject
     */
    AbstractObject(void);

    /*! \brief Destructor of AbstractObject
     */
    virtual ~AbstractObject(void);

    /*! \brief Updates the object
     *
     * This is a very generic function, it should be called everytime beetwen two
     * frames (e.g. for animations or effects).
     * The way the object will be updated depend on said objects
     */
    virtual void update(
        float dt
        /*!< The elapsed time since last update*/) = 0;

    /*! \brief Advances one step closer in the game.
     *
     * Because the game is by its very nature discrete in time, several objects will
     * need to hear this tick.
     * It is in AbstractObject and not Object because out-of-the-game elements
     * such as ObjectManager or some elements of the HUB do need to take it
     * into account.
     */
    virtual void nextStep(void) = 0;

    /*! \brief Indicates wether this object will be removed next frame
     */
    bool isDead(void) const;

protected:
    /*! \brief Destroy the object next frame
     *
     * This actually just set the m_Dead value, the actual deletion is carried
     * out by its ObjectManager
     */
    void die(void);

private:
    bool m_Dead;
    /*!< Is the object to be destroyed? */
};

/*! \todo Have Object actually have a Sprite initializer structure */

/*! \brief Type of every object that are concrete and in the game
 *
 * Such objects all have a sprites, and the update/nextStep function is
 * a non-virtual interface to impl_update and impl_nextStep respectively, that
 * both needs to be implemented
 */
class Object: public AbstractObject
{
public:
    /*! \brief Constructor of Object
     */
    Object(
        Grid &world,
        /*!< Reference to the world the objects live in*/

        sf::Color col,
        /*!< Color of the sprite to use. This is useful to distinguish objects*/

        sf::Vector2i position = sf::Vector2i(0, 0)
        /*!< The starting position of the object*/);

    /*! \brief Destructor of Object
     */
    virtual ~Object(void);

    /*! \brief Acces the current position of the object
     *
     * \return The current position
     */
    sf::Vector2i getPosition(void) const;

    /*! \brief Acces the position of the object at the start of this turn
     *
     * \return The old position
     */
    sf::Vector2i getOldPosition(void) const;

    /*! \brief Updates the object
     *
     * This function is a non-virtual interface overriding of
     * AbstractObject::update, and calls impl_update.
     * It is there to ensure that those invariants stay stable:
     *     - The sprite of an object is always at the same position of said object
     */
    void update(
        float dt
        /*!< Elapsed time since last update*/) final;

    /*! \brief Takes an object to its next step
     *
     * This function is a non-virtual interface overriding of
     * AbstractObject::nextStep, and calls impl_nextStep.
     * It is there to ensure that those invariants stay stable:
     *     -
     */
    void nextStep(void) final;

    /* */
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;


protected:
    /*! \brief Move the object to the case newPos
     */
    void move(
        sf::Vector2i newPos
        /*!< The case to move into*/);

    Grid &m_World;
    /*!< The world the object lives in*/

private:
    /*! \brief Updates the object with respect to that object
     *
     * This function is a pure virtual function to be overrided with each specific
     * objects. It should not take into consideration global invariants such as
     * sprite position.
     */
    virtual void impl_update(
        float dt
        /*!< Elapsed time since last update*/) = 0;

    /*! \brief Takes an object to its next step with respect to that object
     *
     * This function is a pure virtual function to be overriden with each specific
     * objects. It should not take into consideration global invariants.
     */
    virtual void impl_nextStep(void) = 0;

    /*! \brief The sprite to draw the object
     *
     * A circle for now
     */
    struct Sprite: public sf::Drawable
    {
        /*! \brief Constructor of Sprite
         */
        Sprite(
            sf::Color col
            /*!< The color of the circle */);

        /*! \brief Destructor of Sprite
         */
        virtual ~Sprite(void);

        /* */
        void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;

        /*! \brief Set the position of the sprite
         *
         * As all positions in the world will be in their own coordinates and
         * not in pixel coordinates, we need a function to translate between the two.
         *
         * \todo Have a better encapsulation of the conversion
         */
        void setPosition(
            sf::Vector2i v
            /*!< The position to set the sprite to*/);

        sf::CircleShape m_Circle;
        /*!< The content of the sprite*/
    } m_Sprite;
    /*!< Sprite of the object*/

    sf::Vector2i m_Position;
    /*!< The current position of the object on the grid.
     * \warning This should never be changed. Use Object::move instead*/

    sf::Vector2i m_OldPosition;
    /*! \brief The position of the object before moving, or last turn
     */
};

#endif //HEAD_OBJECT
