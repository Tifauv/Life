#include "World.h"

#include <QPainter>


World::World(QWidget* p_parent, const QSize p_size):
QWidget(p_parent),
m_size(p_size),
m_image1(m_size, QImage::Format_Mono),
m_image2(m_size, QImage::Format_Mono),
m_frontImage(&m_image1),
m_backImage(&m_image2),
m_deadColor(QColor("white").rgb()),
m_aliveColor(QColor("darkCyan").rgb()) {
    init();
}


World::World(QWidget* p_parent, int p_width, int p_height):
World(p_parent, QSize(p_width, p_height)) {
}


void World::init() {
    m_image1.setColorCount(2);
    m_image1.setColor(COLOR_DEAD, m_deadColor);
    m_image1.setColor(COLOR_ALIVE, m_aliveColor);
    resetImage(m_image1);

    m_image1.setColorCount(2);
    m_image1.setColor(COLOR_DEAD, m_deadColor);
    m_image1.setColor(COLOR_ALIVE, m_aliveColor);
    resetImage(m_image2);
}


void World::swap() {
    QImage* temp = m_backImage;
    m_backImage = m_frontImage;
    m_frontImage = temp;
    resetImage(*m_backImage);
    emit swapped();
}


void World::setAliveAt(int p_x, int p_y) {
    if (m_backImage->valid(p_x, p_y))
        m_backImage->setPixel(p_x, p_y, COLOR_ALIVE);
}


void World::setDeadAt(int p_x, int p_y) {
    if (m_backImage->valid(p_x, p_y))
        m_backImage->setPixel(p_x, p_y, COLOR_DEAD);
}


uint World::countAliveAround(int p_x, int p_y) const {
    uint countAlive = 0;

    for (int x = p_x-1; x <= p_x+1; p_x++)
        for (int y = p_y-1; y<= p_y+1; p_y++)
            if (m_frontImage->valid(x, y))
                if (m_frontImage->pixel(x, y) == m_aliveColor)
                    countAlive++;

    return countAlive;
}


void World::paintEvent(QPaintEvent* p_event) {
    QPainter painter(this);
    painter.drawImage(0, 0, *m_frontImage, 0, 0, m_size.width(), m_size.height());
}


void World::resetImage(QImage& p_image) {
    p_image.fill(COLOR_DEAD);
}
