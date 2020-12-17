#include <SFML/Graphics.hpp>
#include <Windows.h>

#include "MainMenu.hpp"

int main()
{
				//without console
			//	HWND Hide;
			//	AllocConsole();
			//	Hide = FindWindowA("ConsoleWindowClass", NULL);
			//	ShowWindow(Hide, 0);
				int scrX = GetSystemMetrics(SM_CXSCREEN); //îïòèìàëüíûå ïàðàìåòðû îêíà 
				int scrY = GetSystemMetrics(SM_CYSCREEN);
				sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Go", sf::Style::Close);
				window.setVerticalSyncEnabled(true); //âåðòèêàëüíàÿ ñèíõðîíèçàöèÿ îêíà
				MainMenu menu(scrX, scrY);
				menu.print_window(window);
				return 0;
}
