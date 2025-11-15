#include "Engine.hpp"

#include <QDebug>
#include <QElapsedTimer>

Engine::Engine(QObject* p_parent):
QObject(p_parent),
m_world(nullptr),
m_cellRules(nullptr),
m_step(0) {
}


World* Engine::world() const {
    return m_world;
}


uint Engine::step() const {
    return m_step;
}


void Engine::setWorld(World* p_world) {
    m_world = p_world;
}


void Engine::setCellRules(const CellRules* p_rules) {
    m_cellRules = p_rules;
}


void Engine::init() {
    m_step = 0;
}


void Engine::runStep() {
    QElapsedTimer timer;

    uint step = ++m_step;
    qInfo() << "Engine: [Step " << step << "] Starting...";
    timer.start();
    uint changes = processWorld(*m_world);
    qint64 elapsed = timer.elapsed();
    qInfo() << "Engine: [Step " << step << "] Finished in " << elapsed << " ms : " << changes << " changes.";

    m_world->swap();
    qInfo() << "Engine: [Step " << step << "] World swapped.";

    Q_EMIT worldUpdated(m_world->frontImage());
    Q_EMIT stepFinished(step, changes, elapsed);
    qInfo() << "Engine: [Step " << step << "] Signals emitted.";
}


bool Engine::processCell(World& p_world, int p_x, int p_y) const {
    return m_cellRules->processCell(p_world, p_x, p_y);
}
