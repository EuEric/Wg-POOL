#include <iostream>
#include <string>

#include "BaseMode.hpp"
#include "ATC.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    BaseMode *mode;
    Input input;

    cin >> input;
    ATC::Port = input.getPort();

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