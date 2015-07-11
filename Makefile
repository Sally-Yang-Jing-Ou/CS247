CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -MMD `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJECTS = Card.o Command.o Player.o HumanPlayer.o ComputerPlayer.o Deck.o GameLogic.o Table.o CardTestHarness.o shuffle.o View.o DeckGUI.o Controller.o Observer.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} $(LDFLAGS) -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
