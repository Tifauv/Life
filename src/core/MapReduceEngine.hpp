#ifndef MapReduceEngine_hpp
#define MapReduceEngine_hpp

#include "TiledEngine.hpp"

class MapReduceEngine : public TiledEngine {
    Q_OBJECT
    Q_INTERFACES(TiledEngine)

public:
    explicit MapReduceEngine(std::shared_ptr<World> p_world, CellRules& p_rules);
    virtual ~MapReduceEngine() {}

protected:
    virtual uint processWorld(World&) override;
};

#endif
