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

	return 0;
}
