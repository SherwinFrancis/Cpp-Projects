main: main.o Channel.o Creator.o Person.o User.o Video.o
	g++ main.o Channel.o Creator.o Person.o User.o Video.o -o main
	make clean

main.o: main.cpp
	g++ -c main.cpp

Channel.o: Channel.cpp
	g++ -c Channel.cpp

Creator.o: Creator.cpp
	g++ -c Creator.cpp

Person.o: Person.cpp
	g++ -c Person.cpp

User.o: User.cpp
	g++ -c User.cpp

Video.o: Video.cpp
	g++ -c Video.cpp

clean:
	del *.o

run:
	./main