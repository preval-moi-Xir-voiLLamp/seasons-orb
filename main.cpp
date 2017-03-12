/*! \file main.cpp
 */

/*! \mainpage Season's Orb
 *
 * This is the Technical document for the game Season's Orb. Feel free to wade
 * through!
 *
 * \section General architecture
 * The general architecture is as thus:
 *     -All objects are instances of AbstractObjects and will be updated every
 *     frames
 *     -Objects are almost never created directly. Instead, they are added to an
 *     ObjectManager that will update and manage it properly.
 *     -All objects in the game (excluding HUB or effects for instance) will be
 *     added manually by the Grid
 *
 *  And the layer system is as such:
 *     \todo Draw the architecture layers
 *
 *  \section Guidelines
 *  Here are the guidelines of the current code:
 *      -
 *
 *  \section This documentation
 *  This documentation could be confusing to some, so here are a few guidelines:
 *      -Documentation of members are in the .h and documentation of methods are
 *      in the .cpp. This could be called incoherent, but allows for inline
 *      comments and spacing better.
 */
#include <SFML/Graphics.hpp>
#include "ObjectManager.h"
#include "Grid.h"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Season's Orb");
    sf::Clock c;

    MasterManager allLayers;
    Layer &allObjects = *allLayers.add<Layer>();
    Grid &world = *allObjects.add<Grid>();

    /* As of now, we use a std::map to map a key to its action*/
    /*! \todo Make an Acter class that would allow one to manage this more
     * properly?
     */
    std::map<sf::Keyboard::Key, Action> mapKey =
    {
        {sf::Keyboard::Left, Action::Left},
        {sf::Keyboard::H, Action::Left},
        {sf::Keyboard::Right, Action::Right},
        {sf::Keyboard::L, Action::Right},
        {sf::Keyboard::Up, Action::Up},
        {sf::Keyboard::K, Action::Up},
        {sf::Keyboard::Down, Action::Down},
        {sf::Keyboard::J, Action::Down}
    };

    //Main loop
    while(window.isOpen())
    {
        float dt = c.restart().asSeconds();

        //Event loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
            {
                auto keyAct = mapKey.find(event.key.code);
                if(keyAct != mapKey.end())
                    world.act(keyAct->second);
                else if(event.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }

            default:
                break;
            }
        }

        //update
        allLayers.update(dt);

        //draw
        window.clear();
        window.draw(allLayers);
        window.display();
    }

    return 0;
}
