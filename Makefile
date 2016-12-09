run: linked_list.o single_node.o main.o 
	g++ linked_list.o single_node.o Game.o  main.o -o run
main.o: main.cpp linked_list.o single_node.o  
	g++ -c main.cpp
single_node.o: single_node.h single_node.cpp
	g++ -c single_node.cpp
Game.o: Game.h Game.cpp
	g++ -c Game.cpp
linked_list.o: linked_list.h linked_list.cpp
	g++ -c linked_list.cpp
clean:
	rm -rf *.o
