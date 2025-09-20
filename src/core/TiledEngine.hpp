#ifndef TiledEngine_hpp
#define TiledEngine_hpp

#include "Engine.hpp"
#include <QList>
#include <QRect>

class TiledEngine : public Engine {
    Q_OBJECT
    Q_INTERFACES(Engine)

    Q_PROPERTY(uint tileSize  READ tileSize  WRITE setTileSize)

public:
    explicit TiledEngine(std::shared_ptr<World> p_world, CellRules& p_rules);
    virtual ~TiledEngine() {}

    uint tileSize() const;
    void setTileSize(uint p_size);

protected:
    void prepareTiles(int p_worldWidth, int p_worldHeight);
    
    const QList<QRect>& tiles() const;

    virtual uint processWorld(World&) override;
    virtual uint processTile(World&, const QRect& p_tile);

private:
    uint m_tileSize;
    QList<QRect> m_tiles;
};
Q_DECLARE_INTERFACE(TiledEngine, "TiledEngine")

#endif
