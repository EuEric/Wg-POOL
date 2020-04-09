#include "Client.hpp"

Client::Client()
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    texture.create(800, 600);

    int mousedown = 0;
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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
                lines.clear();
            }
        }

        window.clear(sf::Color::Green);

        window.draw(sprite);

        window.draw(&lines[0], lines.size(), sf::LinesStrip);

        sprite.setTexture(texture);

        window.display();
    }
}
