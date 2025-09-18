#ifndef ThreadedTiledEngine_hpp
#define ThreadedTiledEngine_hpp

#include "TiledEngine.hpp"

class ThreadedTiledEngine : public TiledEngine {
    Q_OBJECT
    Q_INTERFACES(TiledEngine)

public:
    explicit ThreadedTiledEngine(std::shared_ptr<World> p_world, CellRules& p_rules);
    virtual ~ThreadedTiledEngine() {}

protected:
    virtual void processWorld(World&) override;
};

#endif
