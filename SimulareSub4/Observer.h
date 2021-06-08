#pragma once
#include <vector>


class Observer {
private:

public:
	virtual void notify() = 0;
};

class Observable {
private:
	std::vector<Observer*> subscribed;

public:
	void update();

	void addObserver(Observer* ob);

	void removeObserver(Observer* ob);
};
