#ifndef ThreadedEngine_hpp
#define ThreadedEngine_hpp

#include "TiledEngine.hpp"

class ThreadedEngine : public TiledEngine {
    Q_OBJECT
    Q_INTERFACES(TiledEngine)

public:
    explicit ThreadedEngine(std::shared_ptr<World> p_world, CellRules& p_rules);
    virtual ~ThreadedEngine() {}

protected:
    virtual uint processWorld(World&) override;
};

#endif
