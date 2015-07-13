#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <list>
#include <set>
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Model/Player.h"
#include "Model/HumanPlayer.h"
#include "Model/ComputerPlayer.h"
#include "Model/GameLogic.h"
#include <gtkmm/main.h>
#include "View/View.h"
#include "Controller/Controller.h"

using namespace std;

int main(int argc, char ** argv)
{
	Gtk::Main kit(argc, argv);
	GameLogic gameLogic;
	Controller controller(&gameLogic);
	View view(&controller, &gameLogic);
	Gtk::Main::run(view);

	// while (!gameLogic.gameOver()) {
	// 	gameLogic.dealCards();
	// 	gameLogic.beginGame();
	// }

	return 0;
}
