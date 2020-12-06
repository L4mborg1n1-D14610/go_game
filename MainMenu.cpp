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
												delete_flag = true;
												suicide_flag = false;
												while (delete_flag == true) {
																if_delete_stones(stone->check_color());
																if (suicide_flag == true) {
																				//////////////////////////////////
																				list_real_stones.erase(--list_real_stones.end());
																				list_coord_white_stones.erase(--list_coord_white_stones.end());
																				break;
																}	else {
																				sf::Packet packet;
																				packet << stone->get_x() << stone->get_y();
																				socket.send(packet);
																				packet.clear();
																				socket.receive(packet);
																				int x;
																				int y;
																				packet >> x >> y;
																				TableStone* _stone = new TableStone(x, y, *table, !color);
																				list_real_stones.push_back(_stone);
																				break;
																}
												}
								}	else {
												list_real_stones.push_back(stone);
												list_coord_black_stones.push_back(stone->stone_coords(table));
												this->color = true;
												delete_flag = true;
												suicide_flag = false;
												while (delete_flag == true) {
																if_delete_stones(stone->check_color());
																if (suicide_flag == true) {
																				//////////////////////////////////
																				list_real_stones.erase(--list_real_stones.end());
																				list_coord_black_stones.erase(--list_coord_black_stones.end());
																				break;
																}	else {
																				sf::Packet packet;
																				packet << stone->get_x() << stone->get_y();
																				socket.send(packet);
																				packet.clear();
																				socket.receive(packet);
																				int x;
																				int y;
																				packet >> x >> y;
																				TableStone* _stone = new TableStone(x, y, *table, !color);
																				list_real_stones.push_back(_stone);
																				break;
																}
												}
								}
				}
}
std::list<std::pair<int, int>>::iterator& operator+=(std::list < std::pair<int, int>>::iterator& it, int x) {
				for (auto i = 0; i < x; ++i) {
								++it;
				}
				return it;
}
bool check_press(const std::vector<bool>& _vec, int&& a, int&& b) {
				if (a > b) {
								std::swap(a, b);
				}
				for (; a <= b; ++a) {
								if (_vec[a]) {
												return true;
								}
				}
				return false;
}
void MainMenu::print_menu(sf::RenderWindow& window) {
				Button creategame(middlescreenX(scrX), middlescreenY(scrY) / 4, "Create Game", 100); //создание кнопок главного меню
				Button joingame(middlescreenX(scrX), middlescreenY(scrY) / 2, "Join Game", 100);
				Button exitbutton(middlescreenX(scrX), 3 * middlescreenY(scrY) / 4, "Exit", 100);
				Button smallboard(7 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "9x9", 50);
				Button mediumboard(8 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "13x13", 50);
				Button bigboard(9 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 4, "19x19", 50);
				Button WhiteColor(7.5 * middlescreenX(scrX) / 5, 1.5 * middlescreenY(scrY) / 4, "White", 50);
				Button BlackColor(8.5 * middlescreenX(scrX) / 5, 1.5 * middlescreenY(scrY) / 4, "Black", 50);
				Button backbutton(8 * middlescreenX(scrX) / 5, 1.5 * middlescreenY(scrY) / 2, "Back", 50);
				Button writetext(7.5 * middlescreenX(scrX) / 5, middlescreenY(scrY) / 2, "Write lobby name:", 40);
				Button writebutton(8.5 * middlescreenX(scrX) / 5, 0.87 * middlescreenY(scrY) / 2, 40);
				Button create(8 * middlescreenX(scrX) / 5, 1.25 * middlescreenY(scrY) / 2, "Create", 50);
				Button join(8 * middlescreenX(scrX) / 5, 1.25 * middlescreenY(scrY) / 2, "Join", 50);
				std::vector<std::unique_ptr<Button>> buttons; 
				buttons.push_back(std::make_unique<Button>(creategame));  //0
				buttons.push_back(std::make_unique<Button>(joingame));				//1
				buttons.push_back(std::make_unique<Button>(exitbutton));		//2
				buttons.push_back(std::make_unique<Button>(smallboard));		//3
				buttons.push_back(std::make_unique<Button>(mediumboard));	//4
				buttons.push_back(std::make_unique<Button>(bigboard));				//5
				buttons.push_back(std::make_unique<Button>(WhiteColor));		//6
				buttons.push_back(std::make_unique<Button>(BlackColor));		//7
				buttons.push_back(std::make_unique<Button>(backbutton));		//8
				buttons.push_back(std::make_unique<Button>(writetext));			//9
				buttons.push_back(std::make_unique<Button>(writebutton));	//10
				buttons.push_back(std::make_unique<Button>(create));						//11
				buttons.push_back(std::make_unique<Button>(join));								//12
				std::vector <bool> colorflags;
				for (auto i = 0; i < 13; ++i) {
								colorflags.push_back(false);
				}
				std::vector<bool> chooseflags; //choose boardsize&color
				for (auto i = 0; i < 5; ++i) {
								chooseflags.push_back(false);
				}
				bool createflag = false; //флаг для изменения цвета кнопок
				bool joinflag = false;
				menu_table_flag = true;
				while (window.isOpen()) {
								sf::Event event;
								while (window.pollEvent(event)) {
												if (event.type == sf::Event::Closed) {
																window.close();
												}
												if ((*buttons[0]).ifpress(sf::Mouse::getPosition(window))) {
																(*buttons[0]).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				createflag = true;
																				joinflag = false;
																				(*buttons[10]).emptytext();
																}
																colorflags[0] = true;
												}
												if_mouse_not_on_button((*buttons[0]), window, colorflags[0]);
												if ((*buttons[1]).ifpress(sf::Mouse::getPosition(window))) {
																(*buttons[1]).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				joinflag = true;
																				createflag = false;
																				(*buttons[10]).emptytext();
																}
																colorflags[1] = true;
												}
												if_mouse_not_on_button((*buttons[1]), window, colorflags[1]);
												if ((*buttons[2]).ifpress(sf::Mouse::getPosition(window))) {
																(*buttons[2]).changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																				window.close();
																}
																colorflags[2] = true;
												}
												if_mouse_not_on_button((*buttons[2]), window, colorflags[2]);
												if (createflag) {
																if ((*buttons[3]).ifpress(sf::Mouse::getPosition(window))) {
																				if (!check_press(chooseflags, 0, 2)) {
																								(*buttons[3]).changeTextColor();
																				}
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (chooseflags[1]) {
																												(*buttons[4]).changeTextColorBack();
																												chooseflags[1] = false;
																								}
																								if (chooseflags[2]) {
																												(*buttons[5]).changeTextColorBack();
																												chooseflags[2] = false;
																								}
																								chooseflags[0] = true;
																								(*buttons[3]).changeTextColor();
																								board_size = 1;
																				}
																				colorflags[3] = true;
																}
																if ((*buttons[4]).ifpress(sf::Mouse::getPosition(window))) {
																				if (!check_press(chooseflags, 0, 2)) {
																								(*buttons[4]).changeTextColor();
																				}
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (chooseflags[0]) {
																												(*buttons[3]).changeTextColorBack();
																												chooseflags[0] = false;
																								}
																								if (chooseflags[2]) {
																												(*buttons[5]).changeTextColorBack();
																												chooseflags[2] = false;
																								}
																								chooseflags[1] = true;
																								(*buttons[4]).changeTextColor();
																								board_size = 2;
																				}
																				colorflags[4] = true;
																}
																if ((*buttons[5]).ifpress(sf::Mouse::getPosition(window))) {
																				if (!check_press(chooseflags, 0, 2)) {
																								(*buttons[5]).changeTextColor();
																				}
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (chooseflags[0]) {
																												(*buttons[3]).changeTextColorBack();
																												chooseflags[0] = false;
																								}
																								if (chooseflags[1]) {
																												(*buttons[4]).changeTextColorBack();
																												chooseflags[1] = false;
																								}
																								chooseflags[2] = true;
																								(*buttons[5]).changeTextColor();
																								board_size = 3;
																				}
																				colorflags[5] = true;
																}
																if ((*buttons[6]).ifpress(sf::Mouse::getPosition(window))) {
																				if (!check_press(chooseflags, 3, 4)) {
																								(*buttons[6]).changeTextColor();
																				}
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (chooseflags[4]) {
																												(*buttons[7]).changeTextColorBack();
																												chooseflags[4] = false;
																								}
																								chooseflags[3] = true;
																								(*buttons[6]).changeTextColor();
																								color = true;
																				}
																				colorflags[6] = true;
																}
																if ((*buttons[7]).ifpress(sf::Mouse::getPosition(window))) {
																				if (!check_press(chooseflags, 3, 4)) {
																								(*buttons[7]).changeTextColor();
																				}
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (chooseflags[3]) {
																												(*buttons[6]).changeTextColorBack();
																												chooseflags[3] = false;
																								}
																								chooseflags[4] = true;
																								(*buttons[7]).changeTextColor();
																								color = false;
																				}
																				colorflags[7] = true;
																}
																if ((*buttons[8]).ifpress(sf::Mouse::getPosition(window))) {
																				(*buttons[8]).changeTextColor();
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								createflag = false;
																								(*buttons[10]).emptytext();
																				}
																				colorflags[8] = true;
																}
																if_mouse_not_on_button((*buttons[8]), window, colorflags[8]);
																window.draw((*buttons[8]).displayText());
																window.draw((*buttons[9]).displayText());
																if (event.type == sf::Event::TextEntered)
																{
																				// отсекаем не ASCII символы
																				if (event.text.unicode < 128)
																				{
																								(*buttons[10]).add_letter(static_cast<char>(event.text.unicode));
																				}
																}
																if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
																				(*buttons[10]).delete_letter();
																}
																window.draw((*buttons[10]).displayText());
																if ((*buttons[11]).ifpress(sf::Mouse::getPosition(window))) {
																				(*buttons[11]).changeTextColor();
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (check_press(chooseflags, 0, 2) && check_press(chooseflags, 3, 4) && !(*buttons[10]).isempty()) {
																												//////////////////////creategame
																												loby_name = (*buttons[10]).get_text();
																												host_flag = true;
																												ip = "192.168.1.21";
																												sf::Packet packet;
																												socket.connect(ip, 5001);
																												packet << host_flag << loby_name << color << board_size;
																												socket.send(packet);
																												packet.clear();
																												socket.receive(packet);
																												bool creator; //true - loby is created
																												packet >> creator;
																												if (creator) {
																																std::cout << "connected!";
																																creator = false;
																																packet.clear();
																																socket.receive(packet);
																																packet >> creator;
																																if (creator) {
																																				menu_table_flag = false;
																																				break;
																																}
																												}
																								}
																				}
																				colorflags[11] = true;
																}
																if_mouse_not_on_button((*buttons[11]), window, colorflags[11]);
																window.draw((*buttons[11]).displayText());
																if (check_press(chooseflags, 3, 4)) {
																				window.draw((*buttons[7]).displayText());
																				window.draw((*buttons[6]).displayText());
																}
																else {
																				if_mouse_not_on_button((*buttons[7]), window, colorflags[7]);
																				window.draw((*buttons[7]).displayText());
																				if_mouse_not_on_button((*buttons[6]), window, colorflags[6]);
																				window.draw((*buttons[6]).displayText());
																}
																if (check_press(chooseflags, 0, 2)) {
																				window.draw((*buttons[5]).displayText());
																				window.draw((*buttons[4]).displayText());
																				window.draw((*buttons[3]).displayText());
																}
																else {
																				if_mouse_not_on_button((*buttons[5]), window, colorflags[5]);
																				window.draw((*buttons[5]).displayText());
																				if_mouse_not_on_button((*buttons[4]), window, colorflags[4]);
																				window.draw((*buttons[4]).displayText());
																				if_mouse_not_on_button((*buttons[3]), window, colorflags[3]);
																				window.draw((*buttons[3]).displayText());
																}
												}
												if (joinflag) {
																window.draw((*buttons[9]).displayText());
																if (event.type == sf::Event::TextEntered)
																{
																				// отсекаем не ASCII символы
																				if (event.text.unicode < 128)
																				{
																								(*buttons[10]).add_letter(static_cast<char>(event.text.unicode));
																				}
																}
																if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
																				(*buttons[10]).delete_letter();
																}
																window.draw((*buttons[10]).displayText());
																if ((*buttons[12]).ifpress(sf::Mouse::getPosition(window))) {
																				(*buttons[12]).changeTextColor();
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								if (!(*buttons[10]).isempty()) {
																												//////////////////////joingame
																												loby_name = (*buttons[10]).get_text();
																												host_flag = false;
																												ip = "192.168.1.21";
																												sf::Packet packet;
																												socket.connect(ip, 5001);
																												packet << host_flag << loby_name;
																												socket.send(packet);
																												packet.clear();
																												socket.receive(packet);
																												bool creator; //true - loby is created
																												packet >> creator;
																												if (creator) {
																																std::cout << "connected!";
																																packet >> color >> board_size;
																																creator = false;
																																packet.clear();
																																socket.receive(packet);
																																packet >> creator;
																																if (creator) {
																																				menu_table_flag = false;
																																				break;
																																}
																												}
																								}
																				}
																				colorflags[12] = true;
																}
																if ((*buttons[8]).ifpress(sf::Mouse::getPosition(window))) {
																				(*buttons[8]).changeTextColor();
																				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
																								joinflag = false;
																								(*buttons[10]).emptytext();
																				}
																				colorflags[8] = true;
																}
																if_mouse_not_on_button((*buttons[8]), window, colorflags[8]);
																window.draw((*buttons[8]).displayText());
																if_mouse_not_on_button((*buttons[12]), window, colorflags[12]);
																window.draw((*buttons[12]).displayText());
												}
												window.draw((*buttons[0]).displayText());
												window.draw((*buttons[1]).displayText());
												window.draw((*buttons[2]).displayText());
												window.display();
												window.clear();
								}
								if (!menu_table_flag) {
												break;
								}
				}
}
void MainMenu::print_table(sf::RenderWindow& window) {
				Button Push_Stone(10 * scrX / 11, scrY / 20, "Add Stone", 50);
				bool push_flag = false;
				bool begin_flag = false;
				bool dontpush_stone_flag = false;
				TableStone _helperstone(sf::Mouse::getPosition(window), *table, this->color);
				TableStone* helperstone = new TableStone();
				TableStone _pushed_stone(sf::Mouse::getPosition(window), *table, this->color);
				TableStone* pushed_stone = new TableStone();
				while (window.isOpen())
				{
								sf::Event event;
								while (window.pollEvent(event))
								{
												if (event.type == sf::Event::Closed) {
																window.close();
												}
												window.draw((*table).displaytablesprite());
												if ((*table).checkStoneCursor(sf::Mouse::getPosition(window))) {
																if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {

																				if (*pushed_stone == TableStone(sf::Mouse::getPosition(window), *table, color)) {
																								dontpush_stone_flag = false;																				}
																				else {
																								pushed_stone = new TableStone(sf::Mouse::getPosition(window), *table, color);
																								begin_flag = true;
																								dontpush_stone_flag = true;
																				}
																}
															 if (!dontpush_stone_flag) {
																								helperstone = new TableStone(sf::Mouse::getPosition(window), *table, color);
																								window.draw(helperstone->displaystone());
																}
												}
												if (VACANT(pushed_stone->stone_x_coords(table), pushed_stone->stone_y_coords(table)) && begin_flag && dontpush_stone_flag) {
																window.draw(pushed_stone->displaystone());
												}
												if_mouse_not_on_button(Push_Stone, window, push_flag);
												if (Push_Stone.ifpress(sf::Mouse::getPosition(window))) {
																Push_Stone.changeTextColor();
																if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && begin_flag && dontpush_stone_flag) {
																				add_stone(pushed_stone);
																				dontpush_stone_flag = false;
																}
																push_flag = true;
												}
												for (auto it : list_real_stones) {
																window.draw((*it).displaystone());
												}
												window.draw(Push_Stone.displayText());
												window.display();
												window.clear();
								}
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
void MainMenu::if_delete_stones(bool&& color) {
				bool _color;
				if (color) {
								_color = false;
								for (std::list < std::pair<int, int>>::iterator it = list_coord_black_stones.begin();
												it != list_coord_black_stones.end(); ++it) {
												int x = it->first;
												int y = it->second;
												if (check_neighbours(x, y, _color, color)) {
																delete_flag = true;
																return;
												}
												else {
																delete_flag = false;
												}
								}
								_color = true;
								for (std::list < std::pair<int, int>>::iterator it = list_coord_white_stones.begin();
												it != list_coord_white_stones.end(); ++it) {
												int x = it->first;
												int y = it->second;
												if (check_neighbours(x, y, _color, color)) {
																delete_flag = true;
																suicide_flag = true;
																return;
												}
												else {
																delete_flag = false;
												}
								}
				}	else {
								_color = true;
								for (std::list < std::pair<int, int>>::iterator it = list_coord_white_stones.begin();
												it != list_coord_white_stones.end(); ++it) {
												int x = it->first;
												int y = it->second;
												if (check_neighbours(x, y, _color, color)) {
																delete_flag = true;
																return;
												}
												else {
																delete_flag = false;
												}
								}
								_color = false;
								for (std::list < std::pair<int, int>>::iterator it = list_coord_black_stones.begin();
												it != list_coord_black_stones.end(); ++it) {
												int x = it->first;
												int y = it->second;
												if (check_neighbours(x, y, _color, color)) {
																suicide_flag = true;
																delete_flag = true;
																return;
												}
												else {
																delete_flag = false;
												}
								}
				}
}

bool MainMenu::check_neighbours(int& x, int& y,	bool& color, bool& last_color) {    //поменять потом порядок if -  в начале наиболее вероятные события
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
				default: 
								;
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
				  			eated.sort();
				  			eated.erase(std::unique(eated.begin(), eated.end()), eated.end());
				//			eat.sort();
				//			eat.erase(std::unique(eat.begin(), eat.end()), eat.end());
								if (color != last_color) {
												for (std::list<std::pair<int, int>>::iterator it = eated.begin(); it != eated.end(); ++it) {
																delete_stones(*it, color);
												}
								}	else {
												suicide_flag = true;
								}
								return true;
				} 
				return false;
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
							//					eated.push_back(std::make_pair(x, y));
												if (!check_neighbours(x, y, eat, eated, color)) {
																return true;
												}
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
bool MainMenu::check_neighbours(int& _x, int& _y, std::list<std::pair<int, int>>& eat, std::list<std::pair<int, int>>& eated, bool& color) {
				int tablesize;
				int x;
				int y;
				x = _x;
				y = _y;
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
								return true;
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