#pragma once
#include "observer.h"

class Observable {
private:
	virtual void notify() const = 0;

public:
	virtual void addObserver(Observer* ob) = 0;
	virtual void removeObserver(Observer* ob) = 0;
};
