#include <iostream>

#include "BaseMode.cpp"

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
    try
    {
        BaseMode *mode;
        if (strcmp(argv[1], "server") == 0)
        {
            mode = new ServerMode();
        }
        else if (strcmp(argv[1], "client") == 0)
        {
            mode = new ClientMode();
        }
        else
        {
            throw 1438;
        }

        if (dynamic_cast<ServerMode *>(mode))
        {
            cout << "Se porneste serverul on port 1438..." << '\n';
        }
        else
        {
            cout << "Client deschis." << '\n';
        }

        mode->run();
    }
    catch (int e)
    {
        std::cout << "Not a valid argv[1]" << '\n';
    }

    return 0;
}