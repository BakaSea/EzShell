main:main.o DirHelper.h DirHelper.o Command.h Command.o CommandBase.h CommandBase.o
	g++ main.o DirHelper.h DirHelper.o Command.h Command.o CommandBase.h CommandBase.o
main.o:main.cpp
	g++ -c main.cpp
DirHelper.o:DirHelper.cpp
	g++ -c DirHelper.cpp
Command.o:Command.cpp
	g++ -c Command.cpp
CommandBase.o:CommandBase.cpp
	g++ -c CommandBase.cpp

clean:
	rm *.o