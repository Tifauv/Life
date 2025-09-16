#ifndef PatternsLibrary_hpp
#define PatternsLibrary_hpp

#include <memory>

#include "World.hpp"

class PatternsLibrary {
public:
    static void drawGliderAt(std::shared_ptr<World> p_world, uint p_x, uint p_y);
};

#endif
