#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>

#include "Button.hpp"
#include "MainMenu.hpp"
#include "Table.hpp"

int middlescreenX(int& x) {
				return x / 2;
}

const int middlescreenY(int& y) {
				return y / 2;
}
void if_mouse_not_on_button(Button& button, sf::RenderWindow& window, bool flag) {
				if (flag && !button.ifpress(sf::Mouse::getPosition(window))) {
								button.changeTextColorBack();
								flag = false;
				}
}
void menu(sf::RenderWindow& window, int scrX, int scrY) {
				Button creategame(middlescreenX(scrX), middlescreenY(scrY) / 4, "Create Game", 100); //создание кнопок главного меню
				Button joingame(middlescreenX(scrX), middlescreenY(scrY) / 2, "Join Game", 100);
				Button exitbutton(middlescreenX(scrX), 3 * middlescreenY(scrY) / 4, "Exit", 100);
				Button smallboard(7 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "9x9", 50);
				Button mediumboard(8 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "13x13", 50);
				Button bigboard(9 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "19x19", 50);
				Button backbutton(8 * middlescreenX(scrX) / 5, 1.5 * middlescreenY(scrY) / 4, "Back", 50);
				std::vector <bool> colorflags;
				int board_size;
				for (auto i = 0; i < 7; ++i) {
								colorflags.push_back(false);
				}
				bool createflag = false;
				while (window.isOpen())
				{
								sf::Event event;
								while (window.pollEvent(event))
								{
												if (event.type == sf::Event::Closed) {
																window.close();
												}

								}
								if (creategame.ifpress(sf::Mouse::getPosition(window))) {
												creategame.changeTextColor();
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																createflag = true;
												}
												colorflags[0] = true;
								}
								if (joingame.ifpress(sf::Mouse::getPosition(window))) {
												joingame.changeTextColor();
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

												}
												colorflags[1] = true;
								}
								if (exitbutton.ifpress(sf::Mouse::getPosition(window))) {
												exitbutton.changeTextColor();
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																window.close();
												}
												colorflags[2] = true;
								}



								if_mouse_not_on_button(creategame, window, colorflags[0]);
								if_mouse_not_on_button(joingame, window, colorflags[1]);
								if_mouse_not_on_button(exitbutton, window, colorflags[2]);
								window.clear();

								if (createflag) {

												if (smallboard.ifpress(sf::Mouse::getPosition(window))) {
																smallboard.changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				board_size = 1;
																				break;
																}
																colorflags[3] = true;
												}
												if (mediumboard.ifpress(sf::Mouse::getPosition(window))) {
																mediumboard.changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				board_size = 2;
																				break;
																}
																colorflags[4] = true;
												}
												if (bigboard.ifpress(sf::Mouse::getPosition(window))) {
																bigboard.changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				board_size - 3;
																				break;
																}
																colorflags[5] = true;
												}
												if (backbutton.ifpress(sf::Mouse::getPosition(window))) {
																backbutton.changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				createflag = false;
																}
																colorflags[6] = true;
												}

												if_mouse_not_on_button(smallboard, window, colorflags[3]);
												if_mouse_not_on_button(mediumboard, window, colorflags[4]);
												if_mouse_not_on_button(bigboard, window, colorflags[5]);
												if_mouse_not_on_button(backbutton, window, colorflags[6]);
												window.draw(smallboard.displayText());
												window.draw(mediumboard.displayText());
												window.draw(bigboard.displayText());
												window.draw(backbutton.displayText());
								}


								//window.draw(creategame.displayButton());
								window.draw(creategame.displayText());
								//window.draw(exitbutton.displayButton());
								//window.draw(joingame.displayButton());
								window.draw(joingame.displayText());
								window.draw(exitbutton.displayText());



								window.display();
				}
				bool color = true;
				Table table(board_size);
  		MainMenu menu(table);
				while (window.isOpen())
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
				}
}
