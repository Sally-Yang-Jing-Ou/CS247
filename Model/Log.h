#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <string>
#include "Subject.h"

class Log : public Subject {
public:
    Log();
    ~Log();
    std::string getOutput();
    void log(std::string text);
    void clearLog();
private:    
    std::stringstream output_;
};

#endif