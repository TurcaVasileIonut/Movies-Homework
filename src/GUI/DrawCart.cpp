#include "DrawCart.h"

void DrawCartGUI::paintEvent(QPaintEvent* ev){
	QPainter painter{ this };
	painter.setPen(Qt::blue);
	int x = 10, y = 10, w = 10;
	for (auto movie : srv.get_all_from_cart()) {
		painter.drawRect(x, y, w, movie.get_year() % 300);
		x += 40;
	}
}

void DrawCartGUI::update(){
	repaint();
}
	