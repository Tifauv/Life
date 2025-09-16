#ifndef StandardEngine_hpp
#define StandardEngine_hpp

#include "Engine.hpp"

class StandardEngine : public Engine {
    Q_OBJECT
    Q_INTERFACES(Engine)

public:
    explicit StandardEngine(std::shared_ptr<World> p_world);
    ~StandardEngine() {}

public slots:
    void next() override;

signals:
    void finished();

protected:
    void processCell(int p_x, int p_y);
};

#endif
