#include "MainMenu.hpp"
MainMenu::MainMenu(Table &_table) {
    table = &_table;
}
void MainMenu::print_table(sf::RenderWindow& window) {
				window.draw((*table).displaytablesprite());
				for (auto it : vec_stones) {
								window.draw((*it).displaystone());
				}
				window.display();
				window.clear();
}
void MainMenu::add_stone(TableStone* stone/*, sf::RenderWindow& window, bool& color*/) {
			//	if ((*table).checkStoneCursor(sf::Mouse::getPosition(window))) {
								vec_stones.push_back(stone);

				//}
}