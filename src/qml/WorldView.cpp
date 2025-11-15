#include "WorldView.hpp"

#include <QRectF>


WorldView::WorldView(QQuickItem* p_parent):
QQuickPaintedItem(p_parent),
m_zoom(1) {
}


qreal WorldView::implicitWidth() const {
	return m_world->width() * m_zoom;
}


qreal WorldView::implicitHeight() const {
	return m_world->height() * m_zoom;
}

uint WorldView::zoom() const {
	return m_zoom;
}


void WorldView::setZoom(uint p_zoom) {
	m_zoom = p_zoom;
}


World* WorldView::world() const {
	return m_world;
}


void WorldView::setWorld(World* p_world) {
	m_world = p_world;
	update();
}


void WorldView::paint(QPainter* p_painter) {
	p_painter->drawImage(
		QRectF(0, 0, width(), height()),
		*m_world->frontImage(),
		QRectF(0, 0, m_world->width(), m_world->height())
	);
}
