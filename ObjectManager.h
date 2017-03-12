/*! \file ObjectManager.h
 */
#ifndef HEAD_OBJECTMANAGER
#define HEAD_OBJECTMANAGER
#include <list>
#include <SFML/Graphics.hpp>
#include "Object.h"

/*! \brief Wrapper around ObjectManager.
 *
 * This class is empty because virtual template functions are not a thing.
 * It is used as a wrapper to allow the definition of MasterManager, an
 * ObjectManager of ObjectManager without converting them to AbstractObject
 */
class Interface_ObjectManager: public AbstractObject
{
};

/*! \brief A class that will manage the creation and the destructions
 * of all objects
 *
 * As ObjectManager is an AbstractObject, it can manage other ObjectManager.
 * An ObjectManager that is inside another one is what is called a Layer.
 * A layer is there to indicate a hierarchy in the overall architecture, as well 
 * as to categorize certain group of objects to perform operations onto them (is
 * this object near any objects of this layer?)
 * For the global architecture of the layers, see \ref {General architecture}
 * Note that the ObjectManager is templated. 
 * Strictly speaking, we could just
 * have a list of objects, however the typing restriction allows one to be
 * clearer as to what objects is to be expected in such a layer, like a kind of
 * type refinement.
 * It also allows one to call specific function on such objects.
 *
 * \warning As of now, updates of the objects are order-sensitive, this means
 * that they get updated in different context, and that the first object will be
 * updated first.
 *
 * \todo Turn m_AliveList into a vector
 * \todo Change nextstep and draw to generic itteration function?
 */
template<typename T = AbstractObject>
class ObjectManager: public Interface_ObjectManager
{
public:
    /*! \brief Constructor for ObjectManager
     */
    ObjectManager() = default;

    ObjectManager(const ObjectManager<T> &) = delete;

    /*! \brief Destructor for ObjectManager
     */
    virtual ~ObjectManager(void);

    /*! \brief Spawns a new object
     *
     * This function will be used to create an object and store it in the
     * ObjectManager
     *
     * \tparam U The type of the object to create. It shall be a subtype of T
     * \tparam Args The list of the type of the arguments
     *
     * \return A pointer to the created object
     */
    template<typename U, typename... Args> U* add(Args&& ... args);

    /*! \brief Update all objects in order that were created by this ObjectManager
     *
     * It is to be noted that the function operates in two steps, first it updates
     * all objects, then it deletes the dead ones.
     * This is because first, we do not want to operate on memory and update at the
     * same time, as some objects might point to an indice that is wrong in some
     * functions and second because it is safer to have all the objects update in
     * the same environment, and not have them modify the environment to the other
     * \todo Further encourage two steps decomposition by having a pre-update
     * function?
     */
    void update(
        float dt
        /*!< Time elapsed since last call of update*/) override;

    /*! \brief Advance all objects to their next step in order
     */
    void nextStep(void) override;

    /*! \brief Draw all the objects that were created by this ObjectManager
     */
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const final;

protected:
    std::list<T*> m_AliveList;
    /*!< The list of all objects created so far*/
};

/*! \brief A generic layer is a layer of AbstractObject*/
typedef ObjectManager<> Layer;

/*! \brief A master manager is an ObjectManager of ObjectManager */
typedef ObjectManager<Interface_ObjectManager> MasterManager;

#include "ObjectManager.tpp"
#endif //HEAD_OBJECTMANAGER
