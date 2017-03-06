#ifndef HEAD_GRID
#define HEAD_GRID
#include "Object.h"

class Grid: public AbstractObject
{
public:
    Grid();
    ~Grid();
    void update(float dt) override; 

private:
};

#endif //HEAD_GRID
