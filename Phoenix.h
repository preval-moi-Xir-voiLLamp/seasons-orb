/*! \file Phoenix.h
 */
#ifndef HEAD_PHOENIX
#define HEAD_PHOENIX
#include "Constant.h"
#include "Object.h"

/*! \brief Main character in the whole game.
 *
 * As of now, the Phoenix simply moves, abiding to the action of the player
 */
class Phoenix: public Object
{
public:
    /*! \brief Constructor of Phoenix
     */
    Phoenix(
        Grid &world
        /*!< Reference to the world the object lives in*/);

    /*! \brief Destructor of Phoenix
     */
    virtual ~Phoenix(void);

private:
    /* */
    void impl_update(float dt) final;

    /* */
    void impl_nextStep(void) final;
};

#endif //HEAD_PHOENIX
