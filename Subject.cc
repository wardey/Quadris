#include "Subject.h"
#include "Observer.h"

void Subject::attach(Observer *o) {
	observers.emplace_back(o);
}

void Subject::notifyObservers() {
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->notify(*this);
	}
}

Subject::~Subject() {}
