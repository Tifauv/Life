#include "BasicEngine.hpp"

#include <iostream>
#include <QDebug>

BasicEngine::BasicEngine(std::shared_ptr<World> p_world, CellRules& p_rules):
Engine(p_world, p_rules) {
}


uint BasicEngine::processWorld(World& p_world) {
    uint changes = 0;
    
    // Process the world grid, one cell at a time
    for (int y=0; y<p_world.height(); y++)
        for (int x=0; x<p_world.width(); x++)
            changes += (cellRules().processCell(p_world, x, y) ? 1 : 0);
    
    return changes;
}
