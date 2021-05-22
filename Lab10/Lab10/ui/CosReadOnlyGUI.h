#pragma once

#include <qwidget.h>
#include <qpainter.h>
#include "../observer/observer.h"
#include "../service/ServiceOferta.h"
#include <utility>


class CosReadOnlyGUI : public QWidget, public Observer {
private:
	ServiceOferta& srv;
	int number_of_elems;

	void paintEvent(QPaintEvent* ev) override;

	/** Draws a rectangle at a random position on the widget. */
	void draw_rect(QPainter& p, const int x, const int y);

	void draw_circle(QPainter& p, const int x, const int y);

	/** Deseneaza una dintre functiile de mai sus, random */
	void draw_something(QPainter& p);

	/** Get a pair of random coords inside the widget. */
	std::pair<int, int> get_random_coords();

public:
	CosReadOnlyGUI(ServiceOferta& service, QWidget* parent = (QWidget*)nullptr);

	void update() override;

	~CosReadOnlyGUI() {
		srv.remove_observer_from_cos(this);
	};
};
