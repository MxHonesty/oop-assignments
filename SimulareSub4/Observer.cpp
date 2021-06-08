#include "Observer.h"

void Observable::update() {
	auto vec = subscribed;
	for (const auto& el : vec) {
		el->notify();
	}
}

void Observable::addObserver(Observer* ob) {
	subscribed.push_back(ob);
}

void Observable::removeObserver(Observer* ob) {
	subscribed.erase(remove(subscribed.begin(), subscribed.end(), ob));
}
