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
void playtable::add_socket(std::shared_ptr<sf::TcpSocket>&& _socket) {
    selector.add(*_socket);
    players.push_back(std::shared_ptr<sf::TcpSocket>(_socket));
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
int playtable::get_tokens_size() {
    return players.size();
}
sf::SocketSelector playtable::get_selector() {
    return selector;
}
void playtable::send_data() {
    if (selector.wait(sf::seconds(10.f))) {
        std::cout << "deb1\n";
        sf::Packet packet;
        sf::Packet packet_client;
        int x;
        int y;
        if (selector.isReady(*players[0])) {
            std::cout << "deb2\n";
            if (players[0]->receive(packet) == sf::Socket::Done) {
                packet >> x >> y;
                packet_client << true << x << y;
                players[1]->send(packet_client);
            }
        } else {
            std::cout << "deb3\n";
            if (players[1]->receive(packet) == sf::Socket::Done) {
                packet >> x >> y;
                packet_client << true << x << y;
                players[0]->send(packet_client);
            }
        }
    }
}


