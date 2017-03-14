#ifndef HEAD_RUNARD
#define HEAD_RUNARD
#include "Phoenix.h"
#include "ObjectManager.h"
class Grid;

class Runard: public Object
{
public:
    /*! \brief Constructor of Runard
     */
    Runard(
        Grid &world,
        /*!< Reference to the world the object lives in*/

        Phoenix &phoenix
        /*! Reference to the phoenix so as to take it into account*/);

    /*! \brief Destructor of Runard
     */
    virtual ~Runard(void);

private:
    /* */
    void impl_update(float dt) final;

    /* */
    void impl_nextStep(void) final;

    Phoenix &m_Phoenix;
    /*!< Reference to the phoenix so as to not bump in it*/
};

typedef ObjectManager<Runard> RunardLayer;

#endif //HEAD_RUNARD
