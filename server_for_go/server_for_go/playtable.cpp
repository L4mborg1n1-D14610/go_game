#include "playtable.hpp"
playtable::playtable(sf::TcpSocket* _socket, std::string& _name, bool& _color, int& size) {
    players.push_back(std::shared_ptr<sf::TcpSocket>(_socket));
    selector.add(*_socket);
    lobby_name = _name;
    color_1 = _color;
    color_2 = !_color;
    table_size = size;
    game_begin = false;
}
void playtable::add_socket(sf::TcpSocket& _socket) {
    selector.add(_socket);
    game_begin = true;
}
std::string playtable::return_lob_name() {
    return lobby_name;
}   
bool playtable::get_other_color() {
    return color_2;
}
int playtable::get_tablesize() {
    return table_size;
}
std::shared_ptr<sf::TcpSocket> playtable::get_first_socket() {
    return players[0];
}
std::shared_ptr<sf::TcpSocket> playtable::get_second_socket() {
    return players[1];
}
bool playtable::get_game_status() {
    return game_begin;
}

