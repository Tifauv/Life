#include "WorldView.hpp"

#include <QPainter>
#include <QRectF>


WorldView::WorldView(std::shared_ptr<World> p_world, QWidget* p_parent):
QWidget(p_parent),
m_world(p_world),
m_zoom(1) {
    QObject::connect(p_world.get(), &World::updated,
                     this,          qOverload<>(&QWidget::update));
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
    return true;
}


int WorldView::heightForWidth(int p_width) const {
    return p_width;
}


void WorldView::paintEvent(QPaintEvent* p_event) {
    QPainter painter(this);
    painter.drawImage(
        QRectF(0, 0, width(), height()),
        m_world->frontImage(),
        QRectF(0, 0, m_world->width(), m_world->height()));
}
