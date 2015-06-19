CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -MMD
OBJECTS = Card.o Command.o Players.o PlayersHuman.o PlayersComputer.o Deck.o GameLogic.o Table.o CardTestHarness.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}