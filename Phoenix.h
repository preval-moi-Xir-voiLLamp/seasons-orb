#ifndef HEAD_PHOENIX
#define HEAD_PHOENIX
#include "Constant.h"
#include "Object.h"

class Phoenix: public Object
{
public:
    Phoenix(const Grid &world);
    virtual ~Phoenix(void);



private:
    void impl_update(float dt) final;
    void impl_nextStep(void) final;
};

#endif //HEAD_PHOENIX
