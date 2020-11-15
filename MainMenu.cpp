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
			 list_real_stones.push_back(stone);
				if (stone->check_color()) {
								list_coord_white_stones.push_back(stone->stone_coords(table));
				} else {
								list_coord_black_stones.push_back(stone->stone_coords(table));
				}
}
void MainMenu::print_menu(sf::RenderWindow& window) {
				Button creategame(middlescreenX(scrX), middlescreenY(scrY) / 4, "Create Game", 100); //�������� ������ �������� ����
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
				bool createflag = false; //���� ��� ��������� ����� ������
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
				int color = true;
				bool help_stones_flag = true;
				TableStone helperstone(sf::Mouse::getPosition(window), *table, color);
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
												}
												else if (help_stones_flag) {
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
								if_delete_stones();
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
				std::list < std::pair<int, int>> must_eat;
				std::list < std::pair<int, int>> must_eated;
				for (std::list < std::pair<int, int>>::iterator it = list_coord_white_stones.begin();
								it != list_coord_white_stones.end(); ++it) {

								must_eat.clear();
								must_eated.clear();
				}
}
std::list<std::pair<int, int>>::iterator& operator+=(std::list < std::pair<int, int>>::iterator& it, int x) {
				for (auto i = 0; i < x; ++i) {
								++it;
				}
				return it;
}
void MainMenu::check_neighbours(std::list<std::pair<int, int>>::iterator it,
				std::list < std::pair<int, int>>& eat,
				std::list < std::pair<int, int>>& eated,
				bool& color) {
				int x = it->first;
				int y = it->second;
				if (VACANT(x, y, color)) {
								if (x == 0 && y == 0) {
												eated.push_back(*it);
												++it;
												check_neighbours(it, eat, eated, color);
												it += table->return_tablesize();
												check_neighbours(it, eat, eated, color);
												--it;
												check_neighbours(it, eat, eated, color);
												eated.sort();
												eated.erase(std::unique(eated.begin(), eated.end()), eated.end());
								}
								else if (x == 0 && y == (table->return_tablesize() - 1)) {

								}
								else if (x == (table->return_tablesize() - 1) && y == 0) {

								}
								else if (x == (table->return_tablesize() - 1) && y == (table->return_tablesize() - 1)) {

								}
								else if (x == 0) {

								}
								else if (x == (table->return_tablesize() - 1)) {

								}
								else if (y == 0) {

								}
								else if (y == (table->return_tablesize() - 1)) {

								}
								else {

								}
				}
}
bool MainMenu::VACANT(int& x, int& y, bool& color) {
				if (color) {
								if (std::find(list_coord_white_stones.begin(), list_coord_white_stones.end(), std::make_pair(x, y))
												!= list_coord_white_stones.end()) {
												return true;
								}
								else {
												return false;
								}
				}	else {
								if (std::find(list_coord_black_stones.begin(), list_coord_black_stones.end(), std::make_pair(x, y))
												!= list_coord_black_stones.end()) {
												return true;
								}
								else {
												return false;
								}
				}
}

