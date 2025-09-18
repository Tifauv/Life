#include "World.hpp"

#include <QDebug>
#include <QPainter>


World::World(const QSize p_size):
m_size(p_size),
m_image1(m_size, QImage::Format_Mono),
m_image2(m_size, QImage::Format_Mono),
m_frontImage(&m_image1),
m_backImage(&m_image2) {
    init();
}


World::World(int p_width, int p_height):
World(QSize(p_width, p_height)) {
}


const QSize World::size() const {
    return m_size;
}


int World::width() const {
    return m_size.width();
}


int World::height() const {
    return m_size.height();
}

const QImage& World::frontImage() const {
    return *m_frontImage;
}


void World::init() {
    m_image1.fill(COLOR_DEAD);
    m_image2.fill(COLOR_DEAD);
}


void World::swap() {
    QImage* temp = m_backImage;
    m_backImage = m_frontImage;
    m_frontImage = temp;
    emit updated();
}


void World::copyCellAt(int p_x, int p_y) {
    if (!m_backImage->valid(p_x, p_y))
        return;

    m_backImage->setPixel(p_x, p_y,
        m_frontImage->pixelIndex(p_x, p_y));
}


void World::setAliveAt(int p_x, int p_y) {
    if (!m_backImage->valid(p_x, p_y))
        return;

    m_backImage->setPixel(p_x, p_y, COLOR_ALIVE);
}


void World::setDeadAt(int p_x, int p_y) {
    if (!m_backImage->valid(p_x, p_y))
        return;

    m_backImage->setPixel(p_x, p_y, COLOR_DEAD);
}


uint World::countAliveAround(int p_x, int p_y) const {
    uint countAlive = 0;

    for (int y = p_y-1; y <= p_y+1; y++)
        for (int x = p_x-1; x <= p_x+1; x++) {
            // Skip the central cell, we want its neighbors
            if (x == p_x && y == p_y)
                continue;

            if (m_frontImage->valid(x, y) && m_frontImage->pixelIndex(x, y) == COLOR_ALIVE)
                countAlive++;
        }

    return countAlive;
}
