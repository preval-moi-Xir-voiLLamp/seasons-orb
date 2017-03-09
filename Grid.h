#ifndef HEAD_GRID
#define HEAD_GRID
#include <list>
#include <vector>
#include "Object.h"
#include "ObjectManager.h"
#include "Phoenix.h"

class Grid: public AbstractObject
{
public:
    Grid();
    ~Grid();
    void update(float dt) override; 
    void draw(sf::RenderTarget &rt, sf::RenderStates s) const override;
    bool canMove(sf::Vector2i position, Direction d) const;
    void act(Action a);
    Action currentAction(void) const;

private: 
    void nextStep(void) override;

    typedef std::vector<std::vector<std::list<Object *>>> World;

    int m_Width;
    int m_Height;
    World m_Grid;
        
    MasterManager m_AllLayers;
    Layer &m_AllCharacters;
    Phoenix &m_Phoenix;

    Action m_Action;
};

#endif //HEAD_GRID
