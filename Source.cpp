#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <iterator>

#include "Button.hpp"
#include "Menu.hpp"
#include "Table.hpp"
#include "TableStone.hpp"
#include "MainMenu.hpp"

int main()
{

				int scrX = GetSystemMetrics(SM_CXSCREEN); //оптимальные параметры окна 
				int scrY = GetSystemMetrics(SM_CYSCREEN);
				sf::RenderWindow window(sf::VideoMode(scrX, scrY), "go", sf::Style::Close);
				window.setVerticalSyncEnabled(true); //вертикальная синхронизация окна
				int size_table = 3;
				MainMenu menu(scrX, scrY);
			//	Table table(size_table);
				//std::vector<TableStone*> stones;
				//menu(window, scrX, scrY);
		//		bool color = true;
		//		MainMenu menu(table);
				menu.print_window(window);
			/*	while (window.isOpen())
				{
								sf::Event event;
								while (window.pollEvent(event))
								{
												if (event.type == sf::Event::Closed) {
																window.close();
												}
								}
								//window.draw(table.displaytablesprite());
								if (table.checkStoneCursor(sf::Mouse::getPosition(window))) {
												menu.add_stone(new TableStone(sf::Mouse::getPosition(window), table, color));
												//TableStone stone(sf::Mouse::getPosition(window), table, color);
												//stones.push_back(new TableStone(sf::Mouse::getPosition(window), table, color));
												//window.draw(stone.displaystone());
								}
							
								//window.draw(stone.displaystone());
								menu.print_table(window);
				}*/
				return 0;
}