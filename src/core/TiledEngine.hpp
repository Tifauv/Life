#ifndef TiledEngine_hpp
#define TiledEngine_hpp

#include <QList>
#include <QRect>

#include "lifecore_export.h"
#include "Engine.hpp"

class LIFECORE_EXPORT TiledEngine : public Engine {
    Q_OBJECT
    Q_INTERFACES(Engine)

    Q_PROPERTY(uint tileSize  READ tileSize  WRITE setTileSize  NOTIFY tileSizeChanged)

public:
    explicit TiledEngine(QObject* p_parent = nullptr);
    virtual ~TiledEngine() {}

    uint tileSize() const;
    void setTileSize(uint p_size);

Q_SIGNALS:
    void tileSizeChanged(uint);

protected:
    void prepareTiles(int p_worldWidth, int p_worldHeight, uint p_tileSize);
    
    const QList<QRect>& tiles() const;

    virtual uint processWorld(World&) override;
    virtual uint processTile(World&, const QRect& p_tile);

private:
    uint m_tileSize;
    QList<QRect> m_tiles;
};
Q_DECLARE_INTERFACE(TiledEngine, "TiledEngine")

#endif
