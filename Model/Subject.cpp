#include <set>
#include <iostream>
#include "Subject.h"
#include "../View/Observer.h"
using namespace std;

void Subject::subscribe (Observer *newView) {
    observers_.insert(newView);
}

void Subject::unsubscribe (Observer *formerView) {
     observers_.erase(formerView);
}

void Subject::notify() {
  Observers::iterator i;
  for (i = observers_.begin(); i != observers_.end(); ++i)
    (*i)->update();
}
