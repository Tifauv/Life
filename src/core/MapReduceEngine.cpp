#include "MapReduceEngine.hpp"

#include <iostream>
#include <QDebug>
#include <QRunnable>
#include <QThreadPool>
#include <QtConcurrent>

MapReduceEngine::MapReduceEngine(std::shared_ptr<World> p_world, CellRules& p_rules):
TiledEngine(p_world, p_rules) {
}


uint MapReduceEngine::processWorld(World& p_world) {
	return QtConcurrent::blockingMappedReduced<uint>(
		tiles(),
		[&](const QRect& tile) { return processTile(p_world, tile); },
		[](uint& result, uint const& i) { result += i;}) ;
}
