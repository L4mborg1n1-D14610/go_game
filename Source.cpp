#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>

#include "Button.hpp"
#include "Menu.hpp"
#include "Table.hpp"

int main()
{

				double scrX = GetSystemMetrics(SM_CXSCREEN); //оптимальные параметры окна 
				double scrY = GetSystemMetrics(SM_CYSCREEN);
				sf::RenderWindow window(sf::VideoMode(scrX, scrY), "go", sf::Style::Close);
				window.setVerticalSyncEnabled(true); //вертикальная синхронизация окна
				Table table(0, 0, 2);


				//menu(window, scrX, scrY);
				while (window.isOpen())
				{
								sf::Event event;
								while (window.pollEvent(event))
								{
												if (event.type == sf::Event::Closed) {
																window.close();
												}
								}
								window.draw(table.displaytablesprite());
								window.display();
								window.clear();
				}
				return 0;
}