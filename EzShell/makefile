main:main.o UI.h UI.o Command.h Command.o CommandBase.h CommandBase.o CommandCP.h CommandCP.o CommandCMP.h CommandCMP.o \
	CommandWC.h CommandWC.o CommandCAT.h CommandCAT.o CommandMAN.h CommandMAN.o CommandECHO.h CommandECHO.o \
	CommandLS.h CommandLS.o CommandPWD.h CommandPWD.o CommandCD.h CommandCD.o CommandMKDIR.h CommandMKDIR.o \
	CommandTOUCH.h CommandTOUCH.o CommandRM.h CommandRM.o CommandRMDIR.h CommandRMDIR.o CommandOther.h CommandOther.o\
	CommandINSTALL.h CommandINSTALL.o CommandUNINSTALL.h CommandUNINSTALL.o WorkShell.h WorkShell.o DirHelper.h DirHelper.o
	g++ main.o UI.h UI.o Command.h Command.o CommandBase.h CommandBase.o CommandCP.h CommandCP.o CommandCMP.h CommandCMP.o \
		CommandWC.h CommandWC.o CommandCAT.h CommandCAT.o CommandMAN.h CommandMAN.o CommandECHO.h CommandECHO.o \
		CommandLS.h CommandLS.o CommandPWD.h CommandPWD.o CommandCD.h CommandCD.o CommandMKDIR.h CommandMKDIR.o \
		CommandTOUCH.h CommandTOUCH.o CommandRM.h CommandRM.o CommandRMDIR.h CommandRMDIR.o CommandOther.h CommandOther.o\
		CommandINSTALL.h CommandINSTALL.o CommandUNINSTALL.h CommandUNINSTALL.o WorkShell.h WorkShell.o DirHelper.h DirHelper.o -o EzShell
main.o:
	g++ -c main.cpp
UI.o:UI.cpp
	g++ -c UI.cpp
DirHelper.o:DirHelper.cpp
	g++ -c DirHelper.cpp
WorkShell.o:WorkShell.cpp
	g++ -c WorkShell.cpp
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
CommandLS.o:CommandLS.cpp
	g++ -c CommandLS.cpp
CommandPWD.o:CommandPWD.cpp
	g++ -c CommandPWD.cpp
CommandCD.o:CommandCD.cpp
	g++ -c CommandCD.cpp
CommandMKDIR.o:CommandMKDIR.cpp
	g++ -c CommandMKDIR.cpp
CommandTOUCH.o:CommandTOUCH.cpp
	g++ -c CommandTOUCH.cpp
CommandRM.o:CommandRM.cpp
	g++ -c CommandRM.cpp
CommandRMDIR.o:CommandRMDIR.cpp
	g++ -c CommandRMDIR.cpp
CommandOther.o:CommandOther.cpp
	g++ -c CommandOther.cpp
CommandINSTALL.o:CommandINSTALL.cpp
	g++ -c CommandINSTALL.cpp
CommandUNINSTALL.o:CommandUNINSTALL.cpp
	g++ -c CommandUNINSTALL.cpp
clean:
	rm *.o
	rm EzShell

