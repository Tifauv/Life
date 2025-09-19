#include "ThreadedEngine.hpp"

#include <iostream>
#include <QDebug>
#include <QRunnable>
#include <QThreadPool>

ThreadedEngine::ThreadedEngine(std::shared_ptr<World> p_world, CellRules& p_rules):
TiledEngine(p_world, p_rules) {
}


uint ThreadedEngine::processWorld(World& p_world) {
	uint changes = 1;
	QThreadPool pool;
	
	foreach (auto const tile, tiles())
		pool.start(QRunnable::create([&, tile] {
			processTile(p_world, tile);
		}));
	
	pool.waitForDone();
	return changes;
}
