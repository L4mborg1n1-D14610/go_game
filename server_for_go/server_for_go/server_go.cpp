#include "server_go.hpp"
server_go::server_go() {
    ip = sf::IpAddress::getPublicAddress();
    listener.listen(5001);
    std::cout << "Server is running on ip : " << ip << " port: 5001\n";
    std::thread waiting_th(wait_new, this);
    waiting_th.join();
    std::thread handler_th(clients_handler, this);
    handler_th.join();
}
void server_go::wait_new(server_go* obj) {
    obj->listener.listen(2001);
    obj->selector.add(obj->listener);
    while (true) {
        if (obj->selector.wait()) {
            if (obj->selector.isReady(obj->listener)) {
                sf::TcpSocket* socket = new sf::TcpSocket;
                std::shared_ptr<sf::TcpSocket> sh_sock;
                obj->listener.accept(*socket);
                sf::Packet packet;
                if (socket->receive(packet) == sf::Socket::Done) {
                    sf::IpAddress ip_client;
                    bool type; //true - create, false - join
                    std::string loby_name;
                    packet >> type >> loby_name;
                    sf::Packet packet_client;
                    if (type) {
                        if (std::find(obj->lob_names.begin(), obj->lob_names.end(), loby_name) == obj->lob_names.end()) {
                            //create lobby
                            bool color;
                            int size;
                            packet >> color >> size;
                            std::cout << "created lobby with name: " << loby_name << std::endl;
                            obj->lob_names.push_back(loby_name);
                            obj->lobbys.push_back(std::make_shared<playtable>(playtable(socket, loby_name, color, size)));
                            packet_client << true;
                            auto _it = obj->lobbys.end();
                            --_it;
                            obj->clients.push_back(std::shared_ptr<sf::TcpSocket>((*_it)->get_first_socket()));
                            socket->send(packet_client);
                        } else {
                            //can't create lobby
                            packet_client << false;
                            socket->send(packet_client);
                        }
                    } else {
                        auto it = std::find_if(obj->lobbys.begin(), obj->lobbys.end(), [&](const std::shared_ptr<playtable>& pt) {
                            return pt->return_lob_name() == loby_name;
                            });
                        if (it != obj->lobbys.end() && !(*it)->get_game_status()) {
                            std::cout << "connected to lobby with name: " << loby_name << std::endl;
                            //connect to lobby
                            (*it)->add_socket(*socket);
                            sf::Packet packet_host;
                            packet_host << true;
                            //message for host - true
                            (*it)->get_first_socket()->send(packet_host);
                            obj->clients.push_back(std::shared_ptr<sf::TcpSocket>((*it)->get_second_socket()));
                            packet_client << true << (*it)->get_other_color() << (*it)->get_tablesize();
                            obj->games.push_back(std::shared_ptr<playtable>(*it));
                            obj->lobbys.erase(it);
                            //message for client true-color-size
                            socket->send(packet_client);
                        } else {
                            //can't connect to lobby
                            packet_client << false;
                            socket->send(packet_client);
                        }
                    }

                }
                obj->selector.add(*socket);
            }
        }
    }
}
void server_go::clients_handler(server_go* obj) {
    while (true) {
        for (std::vector<std::shared_ptr<sf::TcpSocket>>::iterator it = obj->clients.begin();
            it != obj->clients.end(); ++it) {
            if (obj->selector.isReady(**it)) {
                int x;
                int y;
                sf::Packet packet;
                if ((*it)->receive(packet) == sf::Socket::Done) {
                    auto it_1 = std::find_if(obj->lobbys.begin(), obj->lobbys.end(), [&](const std::shared_ptr<playtable>& pt) {
                        return pt->get_first_socket() == *it;
                        });
                    if (it_1 == obj->lobbys.end()) {
                        it_1 = std::find_if(obj->lobbys.begin(), obj->lobbys.end(), [&](const std::shared_ptr<playtable>& pt) {
                            return pt->get_second_socket() == *it;
                            });
                        (*it_1)->get_first_socket()->send(packet);
                    } else {
                        (*it_1)->get_second_socket()->send(packet);
                    }
                }
            }
        }
    } 
}
