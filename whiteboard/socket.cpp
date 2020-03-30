#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <thread>
#include <string>
#include <cstring>
#include <map>
#include <SFML/Graphics.hpp>
#include <arpa/inet.h>

class Server
{
private:
    static const int Port = 4501;
    sockaddr_in address;
    int server_fd;
    static bool dataToBeSend;
    static std::string s;
    static std::vector<int> poolClients;
    static sf::Texture currentTexture;

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

    static void server_speaks(sf::Vertex foo, int without)
    {
        for (auto &it : poolClients)
        {
            if (it != without)
                write(it, &foo, sizeof(foo));
        }
    }

    static void connection_thread(int new_socket)
    {
        while (true)
        {
            sf::Vertex foo;
            int valread = read(new_socket, &foo, sizeof(foo));
            Server::server_speaks(foo, new_socket);
            std::cout << "L-am primit de la: " << new_socket << '\n';
            // write(new_socket, &foo, sizeof(foo));
        }
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

class Client
{
private:
    static const int Port = 4501;
    sockaddr_in serv_addr;
    static int sock;
    static sf::Texture texture;
    static sf::Sprite sprite;
    static std::vector<sf::Vertex> lines;

public:
    Client()
    {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            std::cout << "Cannot create socket." << '\n';
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(Port);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
        }

        // std::thread(recive_smth).detach();
        // std::thread(emit).detach();

        // while (true)
        // {
        // }
        // run();
    }

    static void recive_smth()
    {
        while (true)
        {
            sf::Vertex foo;
            int valread = read(sock, &foo, sizeof(foo));
            lines.push_back(foo);
            // std::cout << "Am primit o textura" << '\n';
            //TODO: nuj cum sa desenez noul sprite
            // texture = foo;
        }
    }

    static void emit(sf::Vertex foo)
    {
        write(sock, &foo, sizeof(foo));
    }

    void run()
    {
        std::thread(recive_smth).detach();

        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        // std::vector<sf::Vertex> lines;
        // sf::Texture texture;
        // sf::Sprite sprite;

        texture.create(800, 600);

        int mousedown = 0;
        // run the program as long as the window is open
        window.setFramerateLimit(30);

        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
                else if ((event.type == sf::Event::MouseMoved) && (mousedown == 1))
                {
                    lines.push_back(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(window))));
                    Client::emit(sf::Vector2f(sf::Mouse::getPosition(window)));
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    mousedown = 1;
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    mousedown = 0;
                    texture.update(window);
                    // std::cout << lines.size() << '\n';
                    lines.clear();
                    // Client::emit(sprite);
                }
            }

            window.clear(sf::Color::Red);

            window.draw(sprite);

            window.draw(&lines[0], lines.size(), sf::LinesStrip);

            sprite.setTexture(texture);

            window.display();
        }
    }
};