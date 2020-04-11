#include <iostream>
#include <string>

#include "BaseMode.cpp"
#include "ATC.cpp"

using namespace std;

int ATC::port = int();

Server *Server::pInstance = NULL;

int Client::sock = int();
std::vector<sf::Vertex> Client::lines = std::vector<sf::Vertex>();

int main(int argc, char *argv[])
{
    BaseMode *mode;
    Input input;

    cin >> input;
    ATC::port = input.getPort();

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