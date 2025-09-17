#ifndef BasicEngine_hpp
#define BasicEngine_hpp

#include "Engine.hpp"

class BasicEngine : public Engine {
    Q_OBJECT
    Q_INTERFACES(Engine)

public:
    explicit BasicEngine(std::shared_ptr<World> p_world, CellRules& m_rules);
    ~BasicEngine() {}

protected:
    void processWorld(World&) override;
};

#endif
