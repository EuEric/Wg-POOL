#include <iostream>
#include "socket.cpp"
#include <thread>

using namespace std;

std::vector<int> Server::poolClients = std::vector<int>();
bool Server::dataToBeSend = false;
std::string Server::s = std::string();
sf::Texture Server::currentTexture = sf::Texture();

int Client::sock = int();
sf::Texture Client::texture = sf::Texture();
sf::Sprite Client::sprite = sf::Sprite();
std::vector<sf::Vertex> Client::lines = std::vector<sf::Vertex>();

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "server") == 0)
    {
        std::cout << "Server STARTED" << '\n';
        Server test;
        test.connection();
    }
    else if (strcmp(argv[1], "client") == 0)
    {
        std::cout << "Client launched" << '\n';
        Client test;
        test.run();
    }

    return 0;
}