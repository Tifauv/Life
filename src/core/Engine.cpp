#include "Engine.hpp"

#include <QDebug>
#include <QElapsedTimer>

Engine::Engine(QObject* p_parent):
QObject(p_parent),
m_world(nullptr),
m_cellRules(nullptr) {
}


World* Engine::world() const {
    return m_world;
}


void Engine::setWorld(World* p_world) {
    m_world = p_world;
}


void Engine::setCellRules(const CellRules* p_rules) {
    m_cellRules = p_rules;
}


void Engine::run() {
    QElapsedTimer timer;

    qDebug() << "Starting engine pass...";
    timer.start();
    uint changes = processWorld(*m_world);
    qint64 elapsed = timer.elapsed();
    qDebug() << "Durée : " << elapsed << " (ms)";

    //qDebug() << "Swapping...";
    m_world->swap();

    //qDebug() << "Engine pass finished.";
    Q_EMIT cellsChanged(changes);
    Q_EMIT worldUpdated(m_world->frontImage());
}


bool Engine::processCell(World& p_world, int p_x, int p_y) const {
    return m_cellRules->processCell(p_world, p_x, p_y);
}
