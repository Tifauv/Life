#include "Engine.hpp"

#include <QDebug>

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
    qDebug() << "Starting engine pass...";
    processWorld(*m_world);

    qDebug() << "Swapping...";
    m_world->swap();

    qDebug() << "Engine pass finished.";
    emit finished();
}
