#include "BasicEngine.hpp"

#include <iostream>
#include <QDebug>

BasicEngine::BasicEngine(std::shared_ptr<World> p_world, CellRules& p_rules):
Engine(p_world, p_rules) {
}


void BasicEngine::processWorld(World& p_world) {
    // Process the world grid, one cell at a time
    for (int y=0; y<p_world.height(); y++)
        for (int x=0; x<p_world.width(); x++)
            cellRules().processCell(p_world, x, y);
}
