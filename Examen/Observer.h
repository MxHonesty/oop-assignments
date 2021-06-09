#pragma once
#include <vector>
using std::vector;

// Clasa pur abstracta Observer.
class Observer {
public:
	virtual void notify() = 0;
};


// Clasa Observable.
// Implementeaza tot ce tine de managementul
// Observerilor.
class Observable {
private:
	vector<Observer*> subscribed;

public:

	void update() {
		auto copie = subscribed;  // Pentru rezolvarea problemei
		// Aplearii removeObserver in notify.
		for (auto& el : copie) {
			el->notify();
		}
	}

	// Adauga observerul.
	void addObserver(Observer* ob) {
		subscribed.push_back(ob);
	}
	
	// Elimina observerul.
	void removeObserver(const Observer* ob) {
		subscribed.erase(remove(subscribed.begin(), subscribed.end(), ob));
		// Eliminam din vector folosind erase-remove
	}
};
