class Server
{
private:
    static const int Port = 45002;
    sockaddr_in address;
    int server_fd;
    // static std::vector<std::string> currentChat;
    static bool dataToBeSend;
    static std::string s;
    static std::vector<int> poolClients;
    // static sf::Sprite text;

public:
    Server()
    {
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            std::cout << "Cannot create socket." << '\n';
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(Port);

        if (bind(server_fd, (sockaddr *)&address, sizeof(address)) < 0)
        {
            std::cout << "Cannot bind socket." << '\n';
        }

        if (listen(server_fd, 3) < 0)
        {
            std::cout << "nuj ce face listen si backlog" << '\n';
        }
    }

    static void server_speaks(char *x)
    {
        for (auto &it : poolClients)
        {
            write(it, x, sizeof(x));
        }
    }

    static void connection_thread(int new_socket)
    {
        while (true)
        {
            char buffer[1024] = {0};
            int valread = read(new_socket, buffer, 1024);
            Server::server_speaks(buffer);
        }
        // while (true)
        // {
        //     if (dataToBeSend == true)
        //     {
        //         for (auto &it : poolClients)
        //         {
        //             // int x[] = {1, 2};
        //             // write(it, &text, sizeof(text));
        //         }
        //         dataToBeSend = false;
        //     }
        // }
    }

    void connection()
    {
        //std::thread(server_speaks).detach();
        // std::thread(connection_thread).detach();
        while (true)
        {
            int new_socket, addrlen;
            if ((new_socket = accept(server_fd, (sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                std::cout << "Eroare la acceptare" << '\n';
            }

            std::thread(connection_thread, new_socket).detach();

            std::cout << "NEW CONNECTION" << '\n';

            poolClients.push_back(new_socket);

            //close(new_socket);
        }
    }
};