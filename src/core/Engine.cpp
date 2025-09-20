#include "Engine.hpp"

#include <QDebug>
#include <QElapsedTimer>

Engine::Engine(std::shared_ptr<World> p_world, CellRules& p_rules):
m_world(p_world),
m_cellRules(p_rules) {
}


const World& Engine::world() const {
        return *m_world;
}


CellRules& Engine::cellRules() const {
    return m_cellRules;
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
    emit cellsChanged(changes);
    emit finished();
}
