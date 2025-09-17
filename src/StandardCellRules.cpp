#include "StandardCellRules.hpp"

#include <QDebug>

StandardCellRules::StandardCellRules() :
CellRules() {
}


void StandardCellRules::processCell(World& p_world, int p_x, int p_y) {
    uint neighbors = p_world.countAliveAround(p_x, p_y);
    //qDebug() << "Cell [" << p_x << ", " << p_y <<"] has " << neighbors << " neighbors.";

    switch (neighbors) {
        case 0:
        case 1: p_world.setDeadAt(p_x, p_y);  break;
        case 2: p_world.copyCellAt(p_x, p_y); break;
        case 3: p_world.setAliveAt(p_x, p_y); break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8: p_world.setDeadAt(p_x, p_y);
    }
}
