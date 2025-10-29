#include "BasicEngine.hpp"

#include <iostream>
#include <QDebug>

BasicEngine::BasicEngine(QObject* p_parent):
Engine(p_parent) {
}


uint BasicEngine::processWorld(World& p_world) {
    uint changes = 0;
    
    // Process the world grid, one cell at a time
    for (int y=0; y<p_world.height(); y++)
        for (int x=0; x<p_world.width(); x++)
            changes += (processCell(p_world, x, y) ? 1 : 0);
    
    return changes;
}
