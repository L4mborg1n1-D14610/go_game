#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "MainMenu.hpp"

int main()
{

				int scrX = GetSystemMetrics(SM_CXSCREEN); //оптимальные параметры окна 
				int scrY = GetSystemMetrics(SM_CYSCREEN);
				sf::RenderWindow window(sf::VideoMode(scrX, scrY), "go", sf::Style::Close);
				window.setVerticalSyncEnabled(true); //вертикальная синхронизация окна
				int size_table = 3;
				MainMenu menu(scrX, scrY);
				menu.print_window(window);
				return 0;
}