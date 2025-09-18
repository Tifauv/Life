#include "ThreadedTiledEngine.hpp"

#include <iostream>
#include <QDebug>
#include <QRunnable>
#include <QThreadPool>

ThreadedTiledEngine::ThreadedTiledEngine(std::shared_ptr<World> p_world, CellRules& p_rules):
TiledEngine(p_world, p_rules) {
}


void ThreadedTiledEngine::processWorld(World& p_world) {
	QThreadPool pool;
	
	foreach (auto const tile, tiles())
		pool.start(QRunnable::create([&, tile] {
			processTile(p_world, tile);
		}));
	
	pool.waitForDone();
}
