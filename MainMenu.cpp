#include "MainMenu.hpp"
int MainMenu::middlescreenX(int& x) {
				return x / 2;
}

int MainMenu::middlescreenY(int& y) {
				return y / 2;
}
void MainMenu::if_mouse_not_on_button(Button& button, sf::RenderWindow& window, bool flag) {
				if (flag && !button.ifpress(sf::Mouse::getPosition(window))) {
								button.changeTextColorBack();
								flag = false;
				}
}
MainMenu::MainMenu(int& scrX, int& scrY) {
				this->scrX = scrX;
				this->scrY = scrY;
				menu_table_flag = true;
				board_size = 0;
}
MainMenu::MainMenu(Table& _table) {
				table = &_table;
}

void MainMenu::add_stone(TableStone* stone) {
				if (VACANT(stone->stone_x_coords(table), stone->stone_y_coords(table))) {
								if (stone->check_color()) {
												list_real_stones.push_back(stone);
												list_coord_white_stones.push_back(stone->stone_coords(table));
												this->color = false;
												if_delete_stones();
												if_delete_stones();
												if_delete_stones();
												if_delete_stones();
								}	else {
												list_real_stones.push_back(stone);
												list_coord_black_stones.push_back(stone->stone_coords(table));
												this->color = true;
												if_delete_stones();
												if_delete_stones();
												if_delete_stones();
												if_delete_stones();
								}
				}
}
std::list<std::pair<int, int>>::iterator& operator+=(std::list < std::pair<int, int>>::iterator& it, int x) {
				for (auto i = 0; i < x; ++i) {
								++it;
				}
				return it;
}
void MainMenu::print_menu(sf::RenderWindow& window) {
				Button creategame(middlescreenX(scrX), middlescreenY(scrY) / 4, "Create Game", 100); //создание кнопок главного меню
				Button joingame(middlescreenX(scrX), middlescreenY(scrY) / 2, "Join Game", 100);
				Button exitbutton(middlescreenX(scrX), 3 * middlescreenY(scrY) / 4, "Exit", 100);
				Button smallboard(7 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "9x9", 50);
				Button mediumboard(8 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "13x13", 50);
				Button bigboard(9 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "19x19", 50);
				Button backbutton(8 * middlescreenX(scrX) / 5, 1.5 * middlescreenY(scrY) / 4, "Back", 50);
				std::vector<Button> buttons = { creategame , joingame, exitbutton, smallboard, mediumboard, bigboard, backbutton };
				std::vector <bool> colorflags;
				std::vector<Button>::iterator it_but = buttons.begin();
				for (auto i = 0; i < 7; ++i) {
								colorflags.push_back(false);
				}
				bool createflag = false; //флаг для изменения цвета кнопок
				while (window.isOpen())
				{
								sf::Event event;
								while (window.pollEvent(event))
								{
												if (event.type == sf::Event::Closed) {
																window.close();
												}

								}
								if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
												(*it_but).changeTextColor();
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																createflag = true;
												}
												colorflags[0] = true;
								}
								if_mouse_not_on_button(*it_but, window, colorflags[0]);
								++it_but;
								if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
												(*it_but).changeTextColor();
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																///////////////////////////////////////////////////////////////////////////////////////////////////
												}
												colorflags[1] = true;
								}
								if_mouse_not_on_button(*it_but, window, colorflags[1]);
								++it_but;
								if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
												(*it_but).changeTextColor();
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																window.close();
												}
												colorflags[2] = true;
								}
								if_mouse_not_on_button(*it_but, window, colorflags[2]);
								++it_but;
								if (createflag) {
												if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
																(*it_but).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				board_size = 1;
																				menu_table_flag = false;
																				break;
																}
																colorflags[3] = true;
												}
												++it_but;
												if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
																(*it_but).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				board_size = 2;
																				menu_table_flag = false;
																				break;
																}
																colorflags[4] = true;
												}
												++it_but;
												if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
																(*it_but).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				board_size = 3;
																				menu_table_flag = false;
																				break;
																}
																colorflags[5] = true;
												}
												++it_but;
												if ((*it_but).ifpress(sf::Mouse::getPosition(window))) {
																(*it_but).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				createflag = false;
																}
																colorflags[6] = true;
												}
												if_mouse_not_on_button(*it_but, window, colorflags[6]);
												window.draw((*it_but).displayText());
												--it_but;
												if_mouse_not_on_button(*it_but, window, colorflags[5]);
												window.draw((*it_but).displayText());
												--it_but;
												if_mouse_not_on_button(*it_but, window, colorflags[4]);
												window.draw((*it_but).displayText());
												--it_but;
												if_mouse_not_on_button(*it_but, window, colorflags[3]);
												window.draw((*it_but).displayText());
								}
								it_but = buttons.begin();
								window.draw(buttons[0].displayText());
								++it_but;
								window.draw(buttons[1].displayText());
								++it_but;
								window.draw((*it_but).displayText());
								window.display();
								window.clear();
								it_but = buttons.begin();
				}
}
void MainMenu::print_table(sf::RenderWindow& window) {
				this->color = false;
				bool help_stones_flag = true;
				TableStone helperstone(sf::Mouse::getPosition(window), *table, this->color);
				while (window.isOpen())
				{
								sf::Event event;
								window.draw((*table).displaytablesprite());
								while (window.pollEvent(event))
								{
												if (event.type == sf::Event::Closed) {
																window.close();
												}
								}
								if ((*table).checkStoneCursor(sf::Mouse::getPosition(window))) {
												if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																add_stone(new TableStone(sf::Mouse::getPosition(window), *table, color));
												}	else if (help_stones_flag) {
																TableStone st(sf::Mouse::getPosition(window), *table, color);
																helperstone = st;
																help_stones_flag = false;
																window.draw(helperstone.displaystone());
												}
												else if (!help_stones_flag) {
																if (helperstone.check_stone()) {
																				helperstone.change_tablestone(sf::Mouse::getPosition(window), *table, color);
																								window.draw(helperstone.displaystone());
																}
												}
								}
								for (auto it : list_real_stones) {
												window.draw((*it).displaystone());
								}
								window.display();
								window.clear();
				}
}

void MainMenu::print_window(sf::RenderWindow& window) {
				while (window.isOpen()) {
								if (menu_table_flag == true) {
												print_menu(window);
								}
								else {
												Table t(board_size);
												table = &t;
												print_table(window);
								}
				}
}
void MainMenu::if_delete_stones() {
				bool _color = true;
				for (std::list < std::pair<int, int>>::iterator it = list_coord_white_stones.begin();
								it != list_coord_white_stones.end(); ++it) {
								int x = it->first;
								int y = it->second;
								if (check_neighbours(x, y, _color)) {
												return;
								}
				}
				_color = false;
				for (std::list < std::pair<int, int>>::iterator it = list_coord_black_stones.begin();
								it != list_coord_black_stones.end(); ++it) {
								int x = it->first;
								int y = it->second;
								if (check_neighbours(x, y, _color)) {
												return;
								}
				}
}

bool MainMenu::check_neighbours(int& x, int& y,	bool& color) {    //поменять потом порядок if -  в начале наиболее вероятные события
				std::list < std::pair<int, int>> eat;
				std::list < std::pair<int, int>> eated;
				int tablesize;
				switch (table->return_tablesize()) {
				case 1: tablesize = 8;
								break;
				case 2: tablesize = 12;
								break;
				case 3: tablesize = 18;
								break;
				default: break;
				}
				if (NOT_VACANT(x, y, color)) {
								if (x == 0 && y == 0) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if(check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
							 				--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								} else if (x == 0 && y == tablesize) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								} else if (x == tablesize && y == 0) {
												eated.push_back(std::make_pair(x, y));
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}	else if (x == tablesize && y == tablesize) {
												eated.push_back(std::make_pair(x, y));
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}	else if (x == 0) {
												eated.push_back(std::make_pair(x, y));
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++x;
												--y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}	else if (x == tablesize) {
												eated.push_back(std::make_pair(x, y));
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												--y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}	else if (y == 0) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												--y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								} else if (y == tablesize) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}	else {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
				//			eated.sort();
				//			eated.erase(std::unique(eated.begin(), eated.end()), eated.end());
				//			eat.sort();
				//			eat.erase(std::unique(eat.begin(), eat.end()), eat.end());
								for (std::list<std::pair<int, int>>::iterator it = eated.begin(); it != eated.end(); ++it) {
												delete_stones(*it, color);
								}
								return true;
				} return false;
}
void MainMenu::delete_stones(const std::pair<int, int>& eated, bool& color) {
				int table_size = table->return_tablesize();
				std::pair<int, int> stone_coords;
				stone_coords = return_stone_coordinate(eated, table_size);
				list_real_stones.erase(std::find_if(list_real_stones.begin(), list_real_stones.end(),
								[&stone_coords](TableStone* arg) {
												return	arg->stone_coords_pixels() == stone_coords;
				}));
				if (color) {
								list_coord_white_stones.erase(std::find(list_coord_white_stones.begin(),
												list_coord_white_stones.end(), eated));
				}	else {
								list_coord_black_stones.erase(std::find(list_coord_black_stones.begin(),
												list_coord_black_stones.end(), eated));
				}
}
bool MainMenu::check_eat_stone(int& x, int& y, bool& color,
				std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated) {
				if (NOT_VACANT(x, y, color)) {
								if (NOT_VACANT_ANY_LIST(x, y, eated)) {
												check_neighbours(x, y, eat, eated, color);
								}
								return false;
				}	else if (NOT_VACANT(x, y, !color)) {
								if (NOT_VACANT_ANY_LIST(x, y, eat)) {
												eat.push_back(std::make_pair(x, y));
								}
								return false;
				}	else {
								return true;
				}
}
bool MainMenu::NOT_VACANT(int& x, int& y, bool& color) {
				if (color) {
								if (std::find(list_coord_white_stones.begin(), list_coord_white_stones.end(), std::make_pair(x, y))
												== list_coord_white_stones.end()) {
												return false;
								}	else {
												return true;
								}
				}	else {
								if (std::find(list_coord_black_stones.begin(), list_coord_black_stones.end(), std::make_pair(x, y))
												== list_coord_black_stones.end()) {
												return false;
								}	else {
												return true;
								}
				}
}
bool MainMenu::NOT_VACANT(int& x, int& y, bool&& color) {
				if (color) {
								if (std::find(list_coord_white_stones.begin(), list_coord_white_stones.end(), std::make_pair(x, y))
												== list_coord_white_stones.end()) {
												return false;
								}
								else {
												return true;
								}
				}	else {
								if (std::find(list_coord_black_stones.begin(), list_coord_black_stones.end(), std::make_pair(x, y))
												== list_coord_black_stones.end()) {
												return false;
								}
								else {
												return true;
								}
				}
}
bool MainMenu::VACANT(int&& x, int&& y) {
	 		if ((std::find(list_coord_white_stones.begin(), list_coord_white_stones.end(), std::make_pair(x, y))
	 						== list_coord_white_stones.end())
	 						&& (std::find(list_coord_black_stones.begin(), list_coord_black_stones.end(), std::make_pair(x, y))
	 										== list_coord_black_stones.end())) {
	 						return true;
	 		}
	 		else {
	 						return false;
	 		}
}
bool MainMenu::NOT_VACANT_ANY_LIST(int& x, int& y, std::list<std::pair<int, int>> _list) {
				if (std::find(_list.begin(), _list.end(), std::make_pair(x, y))	== _list.end()) {
								return true;
				}	else {
								return false;
				}
}
bool MainMenu::check_neighbours(int& x, int& y, std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated, bool& color) {
				int tablesize = table->return_tablesize() - 1;
				if (NOT_VACANT(x, y, color)) {
								if (x == 0 && y == 0) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (x == 0 && y == tablesize) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (x == tablesize && y == 0) {
												eated.push_back(std::make_pair(x, y));
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (x == tablesize && y == tablesize) {
												eated.push_back(std::make_pair(x, y));
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (x == 0) {
												eated.push_back(std::make_pair(x, y));
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++x;
												--y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (x == tablesize) {
												eated.push_back(std::make_pair(x, y));
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												--y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (y == 0) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												--y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else if (y == tablesize) {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
								else {
												eated.push_back(std::make_pair(x, y));
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--y;
												--x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												--x;
												++y;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
												++y;
												++x;
												if (check_eat_stone(x, y, color, eat, eated)) {
																return false;
												}
								}
				}
}
std::pair<int, int> return_stone_coordinate(const std::pair<int, int>& _pair, int& tablesize) {
				int x;
				int y;
				int i;
				int j;
				i = _pair.first;
				j = _pair.second;
				switch (tablesize) {
				case 1:
								x = round(115 + 77.625 * i);
								y = round(114 + 77.625 * j);
								return std::make_pair(x, y);
								break;
				case 2:
								x = round(83 + 56.33 * i);
								y = round(82 + 56.33 * j);
								return std::make_pair(x, y);
								break;
				case 3:
								x = 59 + 40 * i;
								y = 60 + 40 * j;
								return std::make_pair(x, y);
								break;
				default: break;
				}
}
