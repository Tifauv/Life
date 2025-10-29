#ifndef BasicEngine_hpp
#define BasicEngine_hpp

#include "lifecore_export.h"
#include "Engine.hpp"

class LIFECORE_EXPORT BasicEngine : public Engine {
    Q_OBJECT
    Q_INTERFACES(Engine)

public:
    explicit BasicEngine(QObject* p_parent = nullptr);
    ~BasicEngine() {}

protected:
    uint processWorld(World&) override;
};

#endif
