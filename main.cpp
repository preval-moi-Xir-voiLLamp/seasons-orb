#include <SFML/Graphics.hpp>
#include "ObjectManager.h"
#include "Grid.h"

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Breakdown");
	sf::Clock c;	

    MasterManager all_layers;
    Layer *all_objects = all_layers.add<Layer>();

    Grid *world = all_objects->add<Grid>();
    //all_objects->add<Phoenix>(*world);

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
				switch(event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();

				default:
					break;
				}
				break;

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
