main:main.o DirHelper.h DirHelper.o CommandBase.h CommandBase.o
	g++ main.o DirHelper.h DirHelper.o CommandBase.h CommandBase.o
main.o:main.cpp
	g++ -c main.cpp
DirHelper.o:DirHelper.cpp
	g++ -c DirHelper.cpp
CommandBase.o:CommandBase.cpp
	g++ -c CommandBase.cpp

clean:
	rm *.o