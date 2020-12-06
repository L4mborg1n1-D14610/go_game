#include "server_go.hpp"
server_go::server_go() {
    ip_local = sf::IpAddress::getLocalAddress();
    ip_public = sf::IpAddress::getPublicAddress();
    std::cout << "Server is running on local ip: " << ip_local
        << "\n public ip: " << ip_public << "\n port: 5001\n";
    std::thread waiting_th(wait_new, this);
    std::thread handler_th(clients_handler, this);
    waiting_th.join();
    handler_th.join();
}
void server_go::wait_new(server_go* obj) {
    obj->listener.getLocalPort();
    obj->listener.listen(5001);
    obj->selector.add(obj->listener);
    while (true) {
        if (obj->selector.wait(sf::seconds(10.f))) {
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
                            //create lob
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
                            obj->selector.add(*socket);
                        } else {
                            //can't create lobby
                            packet_client << false;
                            socket->send(packet_client);
                        }
                    }
                    else {
                        auto it = std::find_if(obj->lobbys.begin(), obj->lobbys.end(), [&](const std::shared_ptr<playtable>& pt) {
                            return pt->return_lob_name() == loby_name;
                            });
                        if (it != obj->lobbys.end() && !(*it)->get_game_status()) {
                            std::cout << "connected to lobby with name: " << loby_name << std::endl;
                            //connect to lobby
                            (*it)->add_socket(std::shared_ptr<sf::TcpSocket>(socket));
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
                            obj->selector.add(*socket);
                        }
                        else {
                            //can't connect to lobby
                            packet_client << false;
                            socket->send(packet_client);
                        }
                    }
                }
            }
        }
    }
}
void server_go::clients_handler(server_go* obj) {
    while (true) {
        if (obj->selector.wait(sf::seconds(10.f))) {
            for (std::vector<std::shared_ptr<sf::TcpSocket>>::iterator it = obj->clients.begin();
                it != obj->clients.end(); ++it) {
                if (obj->selector.isReady(**it)) {
                    sf::Packet packet;
                    if ((*it)->receive(packet) == sf::Socket::Done) {
                        sf::Packet packet_client;
                        int x;
                        int y;
                        packet >> x >> y;
                        packet_client << x << y;
                        auto it_1 = std::find_if(obj->games.begin(), obj->games.end(), [&](const std::shared_ptr<playtable>& pt) {
                            return pt->get_first_socket() == *it;
                            });
                        if (it_1 != obj->games.end()) {
                            std::cout << "sended for jointer\n";
                            ((**it_1).get_second_socket())->send(packet);
                        }
                        else {
                            it_1 = std::find_if(obj->games.begin(), obj->games.end(), [&](const std::shared_ptr<playtable>& pt) {
                                return pt->get_second_socket() == *it;
                                });
                                std::cout << "sended for creator\n";
                                ((**it_1).get_first_socket())->send(packet);
                        }
                    }
                }
            }
        }
    }
}
