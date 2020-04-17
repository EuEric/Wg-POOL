#include "Client.hpp"

int Client::sock = int();
std::vector<sf::Vertex> Client::lines = std::vector<sf::Vertex>();

Client::Client()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Cannot create socket." << '\n';
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ATC::Port);

    if (inet_pton(AF_INET, ATC::IP_Server.c_str(), &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}

void Client::recive_smth()
{
    while (true)
    {
        sf::Vertex foo;
        int valread = read(sock, &foo, sizeof(foo));
        lines.push_back(foo);
    }
}

void Client::emit(sf::Vertex foo)
{
    write(sock, &foo, sizeof(foo));
}

void Client::run()
{
    std::thread(recive_smth).detach();

    std::unique_ptr<Whiteboard<ATC::WindowSizeX, ATC::WindowSizeY>> window(new Whiteboard<ATC::WindowSizeX, ATC::WindowSizeY>());
    window->startClient(lines, emit);
}

void Client::operator++()
{
    run();
}