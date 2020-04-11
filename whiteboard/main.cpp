#include <iostream>
#include <string>

#include "BaseMode.cpp"

using namespace std;

Server *Server::pInstance = NULL;

int Client::sock = int();
// sf::Texture Client::texture = sf::Texture();
// sf::Sprite Client::sprite = sf::Sprite();
std::vector<sf::Vertex> Client::lines = std::vector<sf::Vertex>();

int main(int argc, char *argv[])
{
    BaseMode *mode;
    Input input;

    cin >> input;

    if (input == 1)
    {
        mode = new ServerMode();
    }
    else
    {
        mode = new ClientMode();
    }

    auto getMode = [](BaseMode *mode) -> string {
        return (dynamic_cast<ServerMode *>(mode) ? "Se porneste serverul on port " : "Client deschis. Connecting on port ");
    };

    cout << getMode(mode) << input << "...\n";
    mode->run();

    return 0;
}