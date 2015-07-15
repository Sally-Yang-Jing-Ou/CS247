CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -MMD `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJECTS = Card.o Command.o Model/Log.o Model/Player.o Model/HumanPlayer.o Model/ComputerPlayer.o Model/Deck.o Model/GameLogic.o Model/Table.o CardTestHarness.o View/View.o View/DeckGUI.o View/PlayerBox.o View/MenuBox.o View/HandBox.o View/PopupMessage.o View/CardTable.o Controller/Controller.o View/Observer.o View/Logger.o Model/Subject.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} $(LDFLAGS) -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
