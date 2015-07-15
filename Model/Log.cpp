#include "Log.h"

using namespace std;

Log::Log() {}

Log::~Log() {}

void Log::log(string text) {
    output_ << text << endl;
    notify();
}

string Log::getOutput() {
    return output_.str();
}