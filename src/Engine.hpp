#ifndef Engine_HPP
#define Engine_HPP

#include <memory>
#include <QObject>

#include "CellRules.hpp"
#include "World.hpp"

class Engine : public QObject {
    Q_OBJECT

public:
    explicit Engine(std::shared_ptr<World> p_world, CellRules& p_rules);
    virtual ~Engine() {}

public slots:
    void run();

signals:
    void cellsChanged(uint);
    void finished();

protected:
    const World& world()     const;
    CellRules&   cellRules() const;

    virtual uint processWorld(World&) = 0;

private:
    std::shared_ptr<World> m_world;
    CellRules&             m_cellRules;
};
Q_DECLARE_INTERFACE(Engine, "Engine")

#endif
