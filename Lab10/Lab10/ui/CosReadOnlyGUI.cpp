#include "CosReadOnlyGUI.h"
#include <iostream>
#include <qrandom.h>

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	for (int i = 0; i < number_of_elems; i++) {
		draw_something(p);
	}
	std::cout << ev;
}

void CosReadOnlyGUI::draw_rect(QPainter& p, const int x, const int y) {
	p.drawRect(x, y, 30, 30);
}

void CosReadOnlyGUI::draw_circle(QPainter& p, const int x, const int y) {
	p.drawEllipse(x, y, 30, 30);
}

void CosReadOnlyGUI::draw_something(QPainter& p) {
	auto pair = get_random_coords();
	const int x = pair.first;
	const int y = pair.second;

	int what = 0;
	what = QRandomGenerator::global()->bounded(100);
	switch (what % 2) {
	case 0:
		draw_rect(p, x, y);
		break;
	case 1:
		draw_circle(p, x, y);
		break;
	}
}


std::pair<int, int> CosReadOnlyGUI::get_random_coords() {
	const int x = QRandomGenerator::global()->bounded(this->width() - 30);
	const int y = QRandomGenerator::global()->bounded(this->height() - 30);
	return std::pair<int, int>(x, y);
}

CosReadOnlyGUI::CosReadOnlyGUI(ServiceOferta& service, QWidget* parent) :
	srv{ service }, QWidget{ parent }, number_of_elems{ 0 } {
	srv.add_observer_to_cos(this);
	QWidget::setAttribute(Qt::WA_DeleteOnClose, true);
	update();
}

void CosReadOnlyGUI::update() {
	number_of_elems = static_cast<int>(srv.vector_cos().size());
	repaint();
}
