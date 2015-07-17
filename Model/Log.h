#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <string>
#include "Subject.h"

class Log : public Subject {
public:
    Log(); //constructor
    ~Log(); //destructor
    std::string getOutput(); //gets log output in string form
    void log(std::string text); //function for adding to log output while notifying view
    void clearLog(); //clears the log
private:    
    std::stringstream output_; //private stream for the log
};

#endif