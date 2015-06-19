CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -MMD
OBJECTS = Card.o Command.o Players.o PlayersHuman.o PlayersComputer.o Deck.o GameLogic.o Table.o CardTestHarness.o shuffle.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	@mkdir -p bin
	${CXX} ${CXXFLAGS} ${OBJECTS} -o bin/${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} bin/

-include ${DEPENDS}
