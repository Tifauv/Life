#ifndef WorldItem_hpp
#define WorldItem_hpp

#include <QtQmlIntegration/qqmlintegration.h>

#include "World.hpp"


class WorldItem : public World {
    Q_OBJECT

    QML_NAMED_ELEMENT(World)

public:
    explicit WorldItem(QObject* p_parent = nullptr);
};

#endif
