#include "TiledEngine.hpp"

#include <iostream>
#include <QDebug>

TiledEngine::TiledEngine(std::shared_ptr<World> p_world, CellRules& p_rules):
Engine(p_world, p_rules),
m_tileSize(8) {
    prepareTiles(p_world->width(), p_world->height());
}


uint TiledEngine::tileSize() const {
    return m_tileSize;
}


void TiledEngine::setTileSize(uint p_size) {
    m_tileSize = p_size;
    prepareTiles(world().width(), world().height());
}


void TiledEngine::prepareTiles(int p_worldWidth, int p_worldHeight) {
    uint horizontalTiles   = p_worldWidth / m_tileSize;
    uint horizontalRemains = p_worldWidth % m_tileSize;
    uint verticalTiles   = p_worldHeight  / m_tileSize;
    uint verticalRemains = p_worldHeight  % m_tileSize;

    bool hasHorizontalRemains = horizontalRemains > 0;
    bool hasVerticalRemains   = verticalRemains   > 0;
    bool hasBlockRemains = hasHorizontalRemains && hasVerticalRemains;

    uint nbTiles = horizontalTiles * verticalTiles
    + (hasHorizontalRemains ? verticalTiles   : 0)
    + (hasVerticalRemains   ? horizontalTiles : 0)
    + (hasBlockRemains ? 1 : 0);

    qDebug() << nbTiles << " tiles :";
    qDebug() << "  - " << (horizontalTiles * verticalTiles) << " tiles with size " << m_tileSize << "x" << m_tileSize;
    qDebug() << "  - " << (hasHorizontalRemains ? verticalTiles : 0) << " vertical tiles with size " << horizontalRemains << "x" << m_tileSize;
    qDebug() << "  - " << (hasVerticalRemains ? horizontalTiles : 0) << " horizontal tiles with size " << m_tileSize << "x" << verticalRemains;
    qDebug() << "  - " << (hasBlockRemains ? 1 : 0) << " block tile with size " << horizontalRemains << "x" << verticalRemains;

    QList<QRect> tiles;
    tiles.reserve(nbTiles);

    // Add all full tiles
    qDebug() << "== " << m_tileSize << "x" << m_tileSize << " tiles :";
    for (uint vertTile=0; vertTile<verticalTiles; vertTile++)
        for (uint horizTile=0; horizTile<horizontalTiles; horizTile++) {
            tiles.append(QRect(horizTile * m_tileSize, vertTile * m_tileSize,
                               m_tileSize, m_tileSize));
            qDebug() << "  [" << (horizTile * m_tileSize) << ", " << (vertTile * m_tileSize) << "]";
        }

        // Add vertical remains
        if (hasVerticalRemains) {
            qDebug() << "== " << horizontalRemains << "x" << m_tileSize << " tiles :";
            for (uint vertTile=0; vertTile<verticalTiles; vertTile++) {
                tiles.append(QRect(p_worldWidth - horizontalRemains, vertTile * m_tileSize,
                                   horizontalRemains, m_tileSize));
                qDebug() << "  [" << (p_worldWidth - horizontalRemains) << ", " << (vertTile * m_tileSize) << "]";
            }
        }

        // Add horizontal remains
        if (hasHorizontalRemains) {
            qDebug() << "== " << m_tileSize << "x" << verticalRemains << " tiles :";
            for (uint horizTile=0; horizTile<horizontalTiles; horizTile++) {
                tiles.append(QRect(horizTile * m_tileSize, p_worldHeight - verticalRemains,
                                   m_tileSize, verticalRemains));
                qDebug() << "  [" << (horizTile * m_tileSize) << ", " << (p_worldHeight -verticalRemains) << "]";
            }
        }

        // Add the remaining block
        if (hasBlockRemains) {
            qDebug() << "== " << horizontalRemains << "x" << verticalRemains << " tiles :";
            tiles.append(QRect(p_worldWidth - horizontalRemains, p_worldHeight - verticalRemains,
                               horizontalRemains, verticalRemains));
            qDebug() << "  [" << (p_worldWidth - horizontalRemains) << ", " << (p_worldHeight - verticalRemains) << "]";
        }

        m_tiles = tiles;
}


const QList<QRect>& TiledEngine::tiles() const {
    return m_tiles;
}


uint TiledEngine::processWorld(World& p_world) {
    uint changes = 0;
    
    // Process the world, tile by tile
    foreach (auto const tile, m_tiles)
        changes += processTile(p_world, tile);
    
    return changes;
}


uint TiledEngine::processTile(World& p_world, const QRect& p_tile) {
    uint changes = 0;

    int startX = p_tile.left();
    int startY = p_tile.top();
    int endX = p_tile.right();
    int endY = p_tile.bottom();

    //qDebug() << "Starting engine pass on tile [" << startX << "," << startY << "] to [" << endX << "," << endY << "]...";

    // Process the tile, one cell at a time
    for (int y=startY; y<=endY; y++)
        for (int x=startX; x<=endX; x++)
            changes += (cellRules().processCell(p_world, x, y) ? 1 : 0);
    
    return changes;
}
