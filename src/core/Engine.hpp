#ifndef Engine_hpp
#define Engine_hpp

#include <memory>
#include <QObject>

#include "lifecore_export.h"
#include "CellRules.hpp"
#include "World.hpp"

class LIFECORE_EXPORT Engine : public QObject {
    Q_OBJECT

    Q_PROPERTY(World*           world      READ world  WRITE setWorld)
    Q_PROPERTY(const CellRules* cellRules              WRITE setCellRules)

public:
    explicit Engine(QObject* p_parent = nullptr);
    virtual ~Engine() {}

    World* world() const;

    void setWorld(World* p_world);
    void setCellRules(const CellRules* p_rules);

public Q_SLOTS:
    void runStep();

Q_SIGNALS:
    void cellsChanged(uint);
    void worldUpdated(QImage*);

protected:
    virtual uint processWorld(World&) = 0;
    virtual bool processCell(World&, int p_x, int p_y) const;

private:
    World*           m_world;
    const CellRules* m_cellRules;
};
Q_DECLARE_INTERFACE(Engine, "Engine")

#endif
