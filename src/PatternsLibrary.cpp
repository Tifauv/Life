#include "PatternsLibrary.h"

void PatternsLibrary::drawWalkerAt(World& p_world, uint p_x, uint p_y) {
    p_world.setAliveAt(p_x  , p_y);
    p_world.setAliveAt(p_x+1, p_y);
    p_world.setAliveAt(p_x+2, p_y);
    p_world.setAliveAt(p_x+2, p_y+1);
    p_world.setAliveAt(p_x+1, p_y+2);
}
