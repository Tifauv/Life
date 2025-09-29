#ifndef CellRules_hpp
#define CellRules_hpp

#include <QObject>

#include "lifecore_export.h"
#include "World.hpp"


class LIFECORE_EXPORT CellRules : public QObject {
    Q_OBJECT

public:
    explicit CellRules();
    virtual ~CellRules() {}

    virtual bool processCell(World& p_world, int p_x, int p_y) = 0;
};
Q_DECLARE_INTERFACE(CellRules, "CellRules")

#endif
