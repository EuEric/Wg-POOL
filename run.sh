cd whiteboard
g++ -std=c++11 main.cpp Client.cpp Server.cpp -o whiteboard-app -lsfml-graphics -lsfml-window -lsfml-system
mv whiteboard-app ../