#include "Server.hpp"

Server *Server::pInstance = nullptr;

Server::Server()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Cannot create socket." << '\n';
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(ATC::Port);

    if (bind(server_fd, (sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Cannot bind socket." << '\n';
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cout << "nuj ce face listen si backlog" << '\n';
    }
}

void Server::server_speaks(sf::Vertex foo, int without)
{
    for (auto &it : poolClients)
    {
        if (it != without)
            write(it, &foo, sizeof(foo));
    }
}

void Server::connection_thread(int new_socket)
{
    while (true)
    {
        sf::Vertex foo;
        int valread = read(new_socket, &foo, sizeof(foo));
        Instance()->server_speaks(foo, new_socket);
    }
}

void Server::connection()
{

    while (true)
    {
        int new_socket, addrlen;
        if ((new_socket = accept(server_fd, (sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cout << "Eroare la acceptare" << '\n';
        }

        std::thread(connection_thread, new_socket).detach();

        std::cout << "New connection on socket: " << new_socket << '\n';

        poolClients.push_back(new_socket);
    }
}

Server *Server::Instance()
{
    if (!pInstance)
    {
        pInstance = new Server;
    }

    return pInstance;
}