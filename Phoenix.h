#ifndef HEAD_PHOENIX
#define HEAD_PHOENIX
#include "Constant.h"
#include "Object.h"

class Phoenix: public Object
{
public:
    Phoenix(const Grid &world);
    virtual ~Phoenix(void);

    void update(float dt) override;
    void nextStep(void) override;


private:
};

#endif //HEAD_PHOENIX
