#ifndef StandardCellRules_hpp
#define StandardCellRules_hpp

#include "CellRules.hpp"


class StandardCellRules : public CellRules {
    Q_OBJECT
    Q_INTERFACES(CellRules)

public:
    explicit StandardCellRules();
    ~StandardCellRules() {}

    void processCell(World& p_world, int p_x, int p_y) override;
};

#endif
