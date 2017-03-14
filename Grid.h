/*! \file Grid.h
 */
#ifndef HEAD_GRID
#define HEAD_GRID
#include <list>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Constant.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Phoenix.h"
#include "Runard.h"

/*! \brief The main class of the game, it will manage all objects that are shown
 * in game.
 *
 * The grid creates its own manager so that it has greater control over it,
 * notably in the update and nextstep function
 *
 * \todo Is it okay for Grid to be an Interface_ObjectManager ?
 */

/*! \todo This is kinda messy. Reorganize all ObjectManager and Refference
 * to substructures. Also have a substructure for the actual grid?
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


    /*! \brief Says wether an object obj can come into the case of position p
     *
     * \return True if the object can be accepted on this case, false otherwise
     */
    bool canTake(
        Object *obj,
        /*!< The object to accept. It is a pointer so we can now wether we want
         * to accept it or not
         */

        sf::Vector2i pos
        /*!< The posiition where the object want to move into */) const;

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

    /*! \brief Updates the position of an Object on the Grid
     *
     * Because most Objects are assumed to be static, it'd be a waste of time to
     * update the position of every one of them. We therefor have this function
     * that corrects the position of an Object.
     *
     * \warning An object is therefor trusted not to change its position without
     * calling this function. This is enforced with Object::move
     */
    void correct(
        Object *obj
        /*!< The object to correct the position of */);


    /* */
    void update(float dt) override;

    /* */
    void nextStep(void) override;

    /* */
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;

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

    RunardLayer &m_AllRunards;
    /*!< Layer of all the runards that are in the game*/

    Action m_Action;
    /*!< The action in the current turn, if there is one*/
};

#endif //HEAD_GRID
