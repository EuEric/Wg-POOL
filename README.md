# Wg-POOL

## Cerințe obligatorii:

- [x] Interfața grafica (în SDL, SFML, Qt, etc) cu API pentru C++
    * https://en.sfml-dev.org/forums/index.php?topic=11577.0

    ```cpp
    // whiteboard/Whiteboard.cpp
    #include <SFML/Graphics.hpp>

    sf::RenderWindow window(sf::VideoMode(X, Y), "My whiteboard");
    ```

- [x] RTTI
    * https://www.geeksforgeeks.org/g-fact-33/

    ```cpp
    // whiteboard/main.cpp
    dynamic_cast<ServerMode *>(mode)
    ```

- [x] Abstract Classes 
    * https://en.wikibooks.org/wiki/C%2B%2B_Programming/Classes/Abstract_Classes

    ```cpp
    // whiteboard/BaseMode.cpp
    class BaseMode {
      virtual void run() = 0;
    };
    ```

- [ ] Operatori (minim 4 * numărul oamenilor din echipa)

    ```cpp
    // whiteboard/BaseMode.cpp
    bool operator==(int x)
    friend std::istream &operator>>(std::istream &in, Input &input)
    friend std::ostream &operator<<(std::ostream &out, const Input &input)
    ```

- [x] Heap Memory Allocation
    * https://www.geeksforgeeks.org/stack-vs-heap-memory-allocation/
    * https://www.learncpp.com/cpp-tutorial/79-the-stack-and-the-heap/

    ```cpp
    // whiteboard/main.cpp
    mode = new ServerMode();
    ```

- [x] Exceptions
    * http://www.cplusplus.com/doc/tutorial/exceptions/

    ```cpp
    // whiteboard/BaseMode.cpp
    try {
      input.port = std::stoi(inputPort);
      throw static_cast<std::string_view>("Invalid mode.");
    }
    catch (...) {
    }
    ```
    
- [x] STL

    ```cpp
    // whiteboard/Server.hpp
    std::vector<int> poolClients;
    ```

- [x] Lambda expressions
    * https://www.drdobbs.com/cpp/lambdas-in-c11/240168241

    ```cpp
    // whiteboard/main.cpp
    auto getMode = [](BaseMode *mode) -> string {...};
    ```

- [x] Templates
    * https://www.programiz.com/cpp-programming/templates

    ```cpp
    // whiteboard/Whiteboard.cpp
    template <int X, int Y>
    class Whiteboard{...};
    ```

- [x] Smart pointers (minim 1 tip / proiect)
    * https://www.geeksforgeeks.org/smart-pointers-cpp/

    ```cpp
    // whiteboard/Client.cpp
    std::unique_ptr<Whiteboard<800, 600>> window(new Whiteboard<800, 600>());
    ```

- [ ] Design patterns (minim 2 * numărul oamenilor din echipa)
    * https://en.wikipedia.org/wiki/Facade_pattern
    * http://www.yolinux.com/TUTORIALS/C++Singleton.html
    * https://sourcemaking.com/design_patterns

    ```cpp
    // whiteboard/Server.cpp - Singleton
    Server *Server::Instance() {
      if (!pInstance) {
        pInstance = new Server;
      }
      return pInstance;
    }
    ```

- [x] Features of C++17/20 (constexpr, consteval, constinit, fold expressions, init statement for if/switch, etc) (minim 1 / proiect)
    * https://github.com/AnthonyCalandra/modern-cpp-features 
    * https://skebanga.github.io/string-view/

    ```cpp
    // whiteboard/BaseMode.cpp
    std::string_view err
    ```
  
## Opțional:

- [ ] Move semantics
- [x] Multithreading (la echipe de 3-4 oameni)
    * http://www.cplusplus.com/reference/thread/thread/detach/
  
    ```cpp
    // whiteboard/Server.cpp
    std::thread(connection_thread, new_socket).detach();
    ```

- [x] Computer Network / Socket Programming (la echipe de 2-4 oameni)
    * https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa

    ```cpp
    // whiteboard/Client.cpp
    write(sock, &foo, sizeof(foo));
    ```

- [ ] BD
