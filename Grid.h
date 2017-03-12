/*! \file Grid.h
 */
#ifndef HEAD_GRID
#define HEAD_GRID
#include <list>
#include <vector>
#include "Object.h"
#include "ObjectManager.h"
#include "Phoenix.h"

/*! \brief The main class of the game, it will manage all objects that are shown
 * in game.
 *
 * The grid creates its own manager so that it has greater control over it,
 * notably in the update and nextstep function
 *
 * \todo Is it okay for Grid to be an Interface_ObjectManager ?
 */
class Grid: public Interface_ObjectManager
{
public:

    /*! \brief Default constructor for the Grid.
     *
     * This is the initialisation of the game.
     */
    Grid(void);

    /*! \brief Destructor of the Grid
    */
    ~Grid(void);

    /* */
    void update(float dt) override;

    /* */
    void nextStep(void) override;

    /* */
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;

    /*! \brief Says wether an object at position p can move toward direction d
     */
    bool canMove(
        sf::Vector2i position,
        /*!< Position of the object to consider*/

        Direction d
        /*!< The direction towards which the object would move*/) const;

    /*! \brief Advance all Objects to a new turn under the Action of the player a
    */
    void act(
        Action a
        /*!< The action of the current turn*/);


    /*! \brief Describes the action that takes place in the current turn.
     *
     * Because Objects updates themselve, the grid will just indicate what the
     * action is, and the Objects will update themselve accordingly
     *
     * \return The current action this turn, or Action::None if we are not in a
     * turn
     */
    Action currentAction(void) const;

private:
    int m_Width;
    /*!< The width of the grid*/

    int m_Height;
    /*!< The height of the grid*/

    std::vector<std::vector<std::list<Object*>>> m_Grid;
    /*!< 2D arrays of list of objects. This contains all the object that are in
     * the game for easy pinpointing*/

    MasterManager m_AllLayers;
    /*!< MasterManager for all game objects. It is created by the grid so the
     * grid can choose when to update it*/

    Layer &m_AllCharacters;
    /*!< Layer of all characters in game*/

    Phoenix &m_Phoenix;
    /*!< Refference to the main character*/

    Action m_Action;
    /*!< The action in the current turn, if there is one*/
};

#endif //HEAD_GRID
