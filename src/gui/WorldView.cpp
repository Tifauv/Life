#include "WorldView.hpp"

#include <QPainter>
#include <QRectF>


WorldView::WorldView(QImage* p_world, QWidget* p_parent):
QWidget(p_parent),
m_world(p_world),
m_zoom(1) {
}


uint WorldView::zoom() const {
    return m_zoom;
}


void WorldView::setZoom(uint p_zoom) {
    m_zoom = p_zoom;
    updateGeometry();
}


QSize WorldView::minimumSizeHint() const {
    return m_world->size() * m_zoom;
}


QSize WorldView::sizeHint() const {
    return m_world->size() * m_zoom;
}


bool WorldView::hasHeightForWidth() const {
    return m_world->height() == m_world->width();
}


int WorldView::heightForWidth(int p_width) const {
    return p_width * m_world->height() / m_world->width();
}


void WorldView::setImage(QImage* p_image) {
    m_world = p_image;
    update();
}


void WorldView::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawImage(
        QRectF(0, 0, width(), height()),
        *m_world,
        QRectF(0, 0, m_world->width(), m_world->height()));
}
