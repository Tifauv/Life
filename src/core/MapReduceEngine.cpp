#include "MapReduceEngine.hpp"

#include <QtConcurrent>

MapReduceEngine::MapReduceEngine(QObject* p_parent):
TiledEngine(p_parent) {
}


uint MapReduceEngine::processWorld(World& p_world) {
	return QtConcurrent::blockingMappedReduced<uint>(
		tiles(),
		[&](const QRect& tile) { return processTile(p_world, tile); },
		[](uint& result, uint const& i) { result += i;}) ;
}
