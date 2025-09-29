#ifndef StandardCellRules_hpp
#define StandardCellRules_hpp

#include "lifecore_export.h"
#include "CellRules.hpp"


class LIFECORE_EXPORT StandardCellRules : public CellRules {
    Q_OBJECT
    Q_INTERFACES(CellRules)

public:
    explicit StandardCellRules();
    ~StandardCellRules() {}

    bool processCell(World& p_world, int p_x, int p_y) override;
};

#endif
