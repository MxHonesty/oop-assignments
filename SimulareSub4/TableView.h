#pragma once
#include <qwidget.h>
#include "Service.h"

class TableViewOpen : public QWidget, public Observer {
private:

	Service& srv;
	vector<Task> elems;

public:

	TableViewOpen(Service& srv) : QWidget{}, srv{ srv } {
		srv.addObserver(this);
		notify();
	};

	void notify() override;

};

class TableViewClosed : public QWidget, public Observer {
private:

	Service& srv;
	vector<Task> elems;

public:

	TableViewClosed(Service& srv) : QWidget{}, srv{ srv } {
		srv.addObserver(this);
		notify();
	};

	void notify() override;

};

class TableViewInProgress : public QWidget, public Observer {
private:

	Service& srv;
	vector<Task> elems;

public:

	TableViewInProgress(Service& srv) : QWidget{}, srv{srv} {
		srv.addObserver(this);
		notify();
	};

	void notify() override;

};
