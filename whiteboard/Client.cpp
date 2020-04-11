#include "Client.hpp"

Client::Client()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Cannot create socket." << '\n';
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ATC::port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
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

    std::unique_ptr<Whiteboard<800, 600>> window(new Whiteboard<800, 600>());
    window->startClient(lines, emit);
}
