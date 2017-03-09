#include <SFML/Graphics.hpp>
#include "ObjectManager.h"
#include "Grid.h"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Season's Orb");
	sf::Clock c;	

    MasterManager all_layers;
    Layer &all_objects = *all_layers.add<Layer>();
    Grid &world = *all_objects.add<Grid>();

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
        all_layers.update(dt);

		//draw
		window.clear();
		window.draw(all_layers);
		window.display();
	}

	return 0;
}
