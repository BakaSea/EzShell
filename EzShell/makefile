main:main.o UI.h UI.o Command.h Command.o CommandBase.h CommandBase.o CommandCP.h CommandCP.o CommandCMP.h CommandCMP.o CommandWC.h CommandWC.o CommandCAT.h CommandCAT.o CommandMAN.h CommandMAN.o CommandECHO.h CommandECHO.o
	g++ main.o UI.h UI.o Command.h Command.o CommandBase.h CommandBase.o CommandCP.h CommandCP.o CommandCMP.h CommandCMP.o CommandWC.h CommandWC.o CommandCAT.h CommandCAT.o CommandMAN.h CommandMAN.o CommandECHO.h CommandECHO.o -o EzShell
main.o:
	g++ -c main.cpp
UI.o:UI.cpp
	g++ -c UI.cpp
Command.o:Command.cpp
	g++ -c Command.cpp
CommandBase.o:CommandBase.cpp
	g++ -c CommandBase.cpp
CommandCP.o:CommandCP.cpp
	g++ -c CommandCP.cpp
CommandCMP.o:CommandCMP.cpp
	g++ -c CommandCMP.cpp
CommandWC.o:CommandWC.cpp
	g++ -c CommandWC.cpp
CommandCAT.o:CommandCAT.cpp
	g++ -c CommandCAT.cpp
CommandMAN.o:CommandMAN.cpp
	g++ -c CommandMAN.cpp
CommandECHO.o:CommandECHO.cpp
	g++ -c CommandECHO.cpp
clean:
	rm *.o
	rm EzShell

