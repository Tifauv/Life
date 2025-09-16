#include "StandardEngine.hpp"

#include <iostream>
#include <QDebug>

StandardEngine::StandardEngine(std::shared_ptr<World> p_world):
Engine(p_world) {
}


void StandardEngine::next() {
    qDebug() << "Starting engine pass...";

    // Process the world grid, one cell at a time
    for (int y=0; y<world()->height(); y++)
        for (int x=0; x<world()->width(); x++)
            processCell(x, y);

    // Swap buffers
    qDebug() << "Swapping...";
    world()->swap();
    emit finished();
    qDebug() << "Engine pass finished.";
}


void StandardEngine::processCell(int p_x, int p_y) {
    uint neighbors = world()->countAliveAround(p_x, p_y);
    //qDebug() << "Cell [" << p_x << ", " << p_y <<"] has " << neighbors << " neighbors.";

    switch (neighbors) {
        case 0: world()->setDeadAt(p_x, p_y);  break;
        case 1: world()->setDeadAt(p_x, p_y);  break;
        case 2: world()->copyCellAt(p_x, p_y); break;
        case 3: world()->setAliveAt(p_x, p_y); break;
        case 4: world()->setDeadAt(p_x, p_y);  break;
        case 5: world()->setDeadAt(p_x, p_y);  break;
        case 6: world()->setDeadAt(p_x, p_y);  break;
        case 7: world()->setDeadAt(p_x, p_y);  break;
        case 8: world()->setDeadAt(p_x, p_y);  break;
    }
}
