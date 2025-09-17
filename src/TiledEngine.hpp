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
    ~TiledEngine() {}

    uint tileSize() const;
    void setTileSize(uint p_size);

protected:
    void prepareTiles(int p_worldWidth, int p_worldHeight);

    void processWorld(World&) override;
    virtual void processTile(World&, const QRect& p_tile);

private:
    uint m_tileSize;
    QList<QRect> m_tiles;
};

#endif
