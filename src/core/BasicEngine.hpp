#ifndef BasicEngine_hpp
#define BasicEngine_hpp

#include "lifecore_export.h"
#include "Engine.hpp"

class LIFECORE_EXPORT BasicEngine : public Engine {
    Q_OBJECT
    Q_INTERFACES(Engine)

public:
    explicit BasicEngine(std::shared_ptr<World> p_world, CellRules& m_rules);
    ~BasicEngine() {}

protected:
    uint processWorld(World&) override;
};

#endif
