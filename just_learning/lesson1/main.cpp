#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include <optional>


int main(){
    sf::TcpSocket socket;
    std::optional<sf::IpAddress> ipOpt = sf::IpAddress::getLocalAddress();

    if(!ipOpt){
        std::cout << "Error getting local address!\n";
        return 1;
    }
    sf::IpAddress ip = *ipOpt;

    char type;
    std::cout << "Enter type connecting; [c] - client, [s] - server";
    std::cin >> type;

    if (type == 's')
    {
        sf::TcpListener listener;
        listener.listen(2000);

        if(listener.accept(socket) != sf::Socket::Status::Done)
        {
            std::cout << "Error!\n";
        }
    }
    else if(type == 'c')
    {
        if (socket.connect(ip, 2000) != sf::Socket::Status::Done)
            {
                std::cout << "Error! \n";
            }
    }

    std::string name;
    std::cout << "Enter your name: \n";
    std::cin >> name;

    socket.setBlocking(false);

    std::string message = " ";
    sf::Packet packet;

    while(true)
    {
        if(GetAsyncKeyState(VK_ESCAPE)){
            std::cin >>message;
        }
        if (message != "")
        {
            packet.clear();
            packet << name << message;

            socket.send(packet);
            message = "";
        }

        if(socket.receive(packet) == sf::Socket::Status::Done){
            std::string nameRec;
            std::string messageRec;
            packet >> nameRec >> messageRec;
            std::cout <<nameRec << ": " << messageRec <<"";
        }
    }
    
    
}