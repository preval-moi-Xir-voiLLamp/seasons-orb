/*! \file ObjectManager.h
 */
#ifndef HEAD_OBJECTMANAGER
#define HEAD_OBJECTMANAGER
#include <list>
#include <SFML/Graphics.hpp>
#include "Object.h"

class Interface_ObjectManager: public AbstractObject
{
};

/*! \brief A class that will manage the creation and the destructions
 * of all objects
 *
 * Note that ObjectManager is itself an AbstractObject. There need not be a
 * single instance of Object Manager, as some objects may have their owns (for
 * instance, for particule effects)
 *
 * \todo Turn m_AliveList into a vector
 */
template<typename T = AbstractObject>
class ObjectManager: public Interface_ObjectManager
{
public:
    ObjectManager() = default;
    ObjectManager(const ObjectManager<T> &) = delete;

    virtual ~ObjectManager(void);
    template<typename U, typename... Args> U* add(Args&& ... args);
    void update(float dt) override;
    void nextStep(void) override;
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const final;

protected:
    std::list<T*> m_AliveList; /*!< The list of all objects created so far*/
};
typedef ObjectManager<> Layer;
typedef ObjectManager<Interface_ObjectManager> MasterManager;

#include "ObjectManager.tpp"
#endif //HEAD_OBJECTMANAGER
