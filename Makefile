CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -MMD
OBJECTS = Card.o Command.o Player.o HumanPlayer.o ComputerPlayer.o Deck.o GameLogic.o Table.o CardTestHarness.o shuffle.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
