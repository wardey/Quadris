#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
class Info;
class Observer;

class Subject {
	std::vector<Observer*> observers;
public:
	void attach(Observer *o);
	void notifyObservers();
	virtual Info getInfo() const = 0;
	virtual Info getPrevInfo() const = 0;
	virtual bool getState() const = 0;
	virtual ~Subject() = 0;
};

#endif
