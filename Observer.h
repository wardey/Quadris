#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Subject;
class Board;

class Observer {
public:
	virtual void notify(Subject &whoNotified) = 0;  // pass the Cell that called
													// the notify method
	virtual ~Observer() = default;
};
#endif
