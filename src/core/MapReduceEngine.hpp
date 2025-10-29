#ifndef MapReduceEngine_hpp
#define MapReduceEngine_hpp

#include "lifecore_export.h"
#include "TiledEngine.hpp"

class LIFECORE_EXPORT MapReduceEngine : public TiledEngine {
    Q_OBJECT
    Q_INTERFACES(TiledEngine)

public:
    explicit MapReduceEngine(QObject* p_parent = nullptr);
    virtual ~MapReduceEngine() {}

protected:
    virtual uint processWorld(World&) override;
};

#endif
