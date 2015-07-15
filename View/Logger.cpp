#include "CardTable.h"
#include <string>
#include "Logger.h"

using namespace std;

Logger::Logger(Controller * controller, GameLogic * gameLogic, Log * log): gameLogic_(gameLogic), controller_(controller), log_(log) {
    set_label("Game Log");

    add(scroller_);
    scroller_.add(logView_);
    logView_.set_editable(false);
    logView_.set_wrap_mode(Gtk::WRAP_WORD);
    logView_.set_size_request(250,-1);

    gameLogic_->subscribe(this);
}

Logger::~Logger() {

}

void Logger::update() {
    logView_.get_buffer()->set_text(log_->getOutput());
}
