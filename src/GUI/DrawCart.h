#pragma once

#include <qwidget.h>
#include <qpainter.h>

#include "Observer.h"
#include "Cart.h"
#include "Service.h"

#ifndef DRAWCART
#define DRAWCART

class DrawCartGUI : public QWidget, public Observer {
private:
	Service &srv;

	void paintEvent(QPaintEvent* ev) override;

public:

	DrawCartGUI(Service& srv) : srv{ srv } {
		repaint();
	};

	/*
	* Update the current window drawing the rectangles for the movies from the current cart
 	*/
	void update() override;

};

#endif