#include "PatternsLibrary.hpp"

void PatternsLibrary::drawGliderAt(std::shared_ptr<World> p_world, uint p_x, uint p_y) {
    p_world->setAliveAt(p_x+1, p_y);
    p_world->setAliveAt(p_x+2, p_y+1);
    p_world->setAliveAt(p_x  , p_y+2);
    p_world->setAliveAt(p_x+1, p_y+2);
    p_world->setAliveAt(p_x+2, p_y+2);
}
