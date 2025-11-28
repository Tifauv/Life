#include "TiledEngine.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <QDebug>

TiledEngine::TiledEngine(QObject* p_parent):
Engine(p_parent),
m_tileSize(8) {
}


uint TiledEngine::tileSize() const {
    return m_tileSize;
}


void TiledEngine::setTileSize(uint p_size) {
    if (p_size > 0 && std::cmp_less(p_size, std::min(world()->width(), world()->height()))) {
        m_tileSize = p_size;
        prepareTiles(world()->width(), world()->height(), p_size);
        Q_EMIT tileSizeChanged(m_tileSize);
    }
}


void TiledEngine::prepareTiles(int p_worldWidth, int p_worldHeight, uint p_tileSize) {
    uint horizontalTiles   = p_worldWidth / p_tileSize;
    uint horizontalRemains = p_worldWidth % p_tileSize;
    uint verticalTiles   = p_worldHeight  / p_tileSize;
    uint verticalRemains = p_worldHeight  % p_tileSize;

    bool hasHorizontalRemains = horizontalRemains > 0;
    bool hasVerticalRemains   = verticalRemains   > 0;
    bool hasBlockRemains = hasHorizontalRemains && hasVerticalRemains;

    uint nbTiles = horizontalTiles * verticalTiles
    + (hasHorizontalRemains ? verticalTiles   : 0)
    + (hasVerticalRemains   ? horizontalTiles : 0)
    + (hasBlockRemains ? 1 : 0);

    qInfo() << nbTiles << " tiles :";
    qInfo() << "  - " << (horizontalTiles * verticalTiles) << " tiles with size " << p_tileSize << "x" << p_tileSize;
    qInfo() << "  - " << (hasHorizontalRemains ? verticalTiles : 0) << " vertical tiles with size " << horizontalRemains << "x" << p_tileSize;
    qInfo() << "  - " << (hasVerticalRemains ? horizontalTiles : 0) << " horizontal tiles with size " << p_tileSize << "x" << verticalRemains;
    qInfo() << "  - " << (hasBlockRemains ? 1 : 0) << " block tile with size " << horizontalRemains << "x" << verticalRemains;

    QList<QRect> tiles;
    tiles.reserve(nbTiles);

    // Add all full tiles
    qDebug() << "== " << p_tileSize << "x" << p_tileSize << " tiles :";
    for (uint vertTile=0; vertTile<verticalTiles; vertTile++) {
        for (uint horizTile=0; horizTile<horizontalTiles; horizTile++) {
            tiles.append(QRect(horizTile * p_tileSize, vertTile * p_tileSize,
                               p_tileSize, p_tileSize));
            qDebug() << "  [" << (horizTile * p_tileSize) << ", " << (vertTile * p_tileSize) << "]";
        }
    }

    // Add vertical remains
    if (hasVerticalRemains) {
        qDebug() << "== " << horizontalRemains << "x" << p_tileSize << " tiles :";
        for (uint vertTile=0; vertTile<verticalTiles; vertTile++) {
            tiles.append(QRect(p_worldWidth - horizontalRemains, vertTile * p_tileSize,
                                horizontalRemains, p_tileSize));
            qDebug() << "  [" << (p_worldWidth - horizontalRemains) << ", " << (vertTile * p_tileSize) << "]";
        }
    }

    // Add horizontal remains
    if (hasHorizontalRemains) {
        qDebug() << "== " << p_tileSize << "x" << verticalRemains << " tiles :";
        for (uint horizTile=0; horizTile<horizontalTiles; horizTile++) {
            tiles.append(QRect(horizTile * p_tileSize, p_worldHeight - verticalRemains,
                               p_tileSize, verticalRemains));
            qDebug() << "  [" << (horizTile * p_tileSize) << ", " << (p_worldHeight -verticalRemains) << "]";
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
    for (auto const tile : m_tiles)
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
        for (int x=startX; x<=endX; x++) {
            if (processCell(p_world, x, y)) {
                qDebug() << "TiledEngine: [Step " << step() << "] Change at [" << x << "," << y << "]";
                changes++;
            }
        }
    
    return changes;
}
