#ifndef MVC_SUBJECT_H
#define MVC_SUBJECT_H

#include <set>

class Observer;

class Subject {
public:
       void subscribe( Observer* );
       void unsubscribe( Observer* );

protected:
       void notify(); //notify views of model change

private:
       typedef std::set< Observer* > Observers;
       Observers observers_;
};

#endif
