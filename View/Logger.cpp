#include "CardTable.h"
#include <string>
#include "Logger.h"

using namespace std;

Logger::Logger(Controller * controller, GameLogic * gameLogic): gameLogic_(gameLogic), controller_(controller) {
    set_label("Game Log");

    add(scroller_);
    scroller_.add(logView_);
    logView_.set_editable(false);
    logView_.set_wrap_mode(Gtk::WRAP_WORD);
    logView_.set_size_request(250,-1);
    // logView_.get_buffer()->set_text("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse vehicula ligula eu magna convallis, quis bibendum elit malesuada. Quisque dignissim massa sed vulputate sagittis. Vivamus vitae posuere turpis. Vivamus viverra ipsum vel ligula efficitur, in lobortis dolor fringilla. Integer et luctus nunc. Pellentesque a dapibus nisl, a ornare lacus. Nullam blandit fermentum nisl eu venenatis. In semper enim fringilla tellus tempor, iaculis facilisis tellus interdum. Cras commodo justo urna, eu elementum ligula suscipit vitae. Nulla scelerisque bibendum lacus id tristique. Sed eu dui at ante consectetur pellentesque. Vivamus diam nisl, mattis eget tristique quis, malesuada ac nibh. Aenean id accumsan felis. Pellentesque pharetra, turpis vel facilisis varius, dui enim imperdiet leo, laoreet pellentesque dolor ipsum sed dui. Morbi ultricies justo nibh. Ut tincidunt ullamcorper nibh, id mattis enim auctor non. Aliquam sollicitudin lectus orci, quis blandit orci scelerisque nec. Phasellus vel lobortis sem. Phasellus euismod ullamcorper urna a sollicitudin. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce sagittis ex malesuada erat consequat ultrices. Mauris non volutpat dolor. Etiam id placerat enim, ut laoreet est. Morbi lacinia ");

    gameLogic_->subscribe(this);
}

Logger::~Logger() {

}

void Logger::update() {

}
