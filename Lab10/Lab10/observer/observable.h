#pragma once
#include "observer.h"
#include <vector>

class Observable {
protected:
	std::vector<Observer*> subscribed;

	void notify() const {
		const auto values{ subscribed };
		for (const auto& el : values)
			el->update();
	}

public:
	void addObserver(Observer* ob) {
		subscribed.push_back(ob);
	}

	void removeObserver(Observer* ob) {
		subscribed.erase(std::remove(subscribed.begin(), subscribed.end(), ob));
	}
};
