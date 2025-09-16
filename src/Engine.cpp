#include "Engine.hpp"

Engine::Engine(std::shared_ptr<World> p_world):
m_world(p_world) {
}


std::shared_ptr<World> Engine::world() const {
    return m_world;
}
