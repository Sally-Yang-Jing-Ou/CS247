#include "Model/GameLogic.h"
#include <gtkmm/main.h>
#include "View/View.h"
#include "Controller/Controller.h"
#include "Model/Log.h"

using namespace std;

int main(int argc, char ** argv)
{
	Gtk::Main kit(argc, argv);
    Log log;
	GameLogic gameLogic(&log);
	Controller controller(&gameLogic, &log);
	View view(&controller, &gameLogic, &log);
	Gtk::Main::run(view);

	return 0;
}
