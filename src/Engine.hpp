#ifndef Engine_HPP
#define Engine_HPP

#include <memory>
#include <QObject>

#include "World.hpp"

class Engine : public QObject {
    Q_OBJECT

public:
    explicit Engine(std::shared_ptr<World> p_world);
    virtual ~Engine() {}

    std::shared_ptr<World> world() const;

public slots:
    virtual void next() = 0;

signals:
    virtual void finished() = 0;

private:
    std::shared_ptr<World> m_world;
};
Q_DECLARE_INTERFACE(Engine, "Engine")

#endif
