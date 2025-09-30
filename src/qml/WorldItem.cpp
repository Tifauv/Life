#include "WorldItem.hpp"

#include <QRectF>


WorldItem::WorldItem(QQuickItem* p_parent):
QQuickPaintedItem(p_parent),
m_zoom(1) {
}


uint WorldItem::zoom() const {
	return m_zoom;
}


void WorldItem::setZoom(uint p_zoom) {
	m_zoom = p_zoom;
}


void WorldItem::setWorld(std::shared_ptr<World> p_world) {
	m_world = p_world;
	update();
}


void WorldItem::paint(QPainter* p_painter) {
	p_painter->drawImage(
		QRectF(0, 0, width(), height()),
		m_world->frontImage(),
		QRectF(0, 0, m_world->width(), m_world->height())
	);
}
