cd whiteboard
g++ -std=c++11 main.cpp Client.cpp Server.cpp ATC.cpp BaseMode.cpp -o myapp-whiteboard -lsfml-graphics -lsfml-window -lsfml-system
mv myapp-whiteboard ../