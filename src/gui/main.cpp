#include <memory>
#include <QApplication>

#include "World.hpp"
#include "PatternsLibrary.hpp"
#include "MapReduceEngine.hpp"
#include "StandardCellRules.hpp"

#include "MainWindow.hpp"


int main(int p_argc, char* p_argv[]) {
	QApplication app(p_argc, p_argv);
	QApplication::setOrganizationName(QStringLiteral("CatWitch"));
	QApplication::setOrganizationDomain(QStringLiteral("catwitch.eu"));
	QApplication::setApplicationName(QStringLiteral("Life"));
	QApplication::setDesktopFileName(QStringLiteral("eu.catwitch.life"));

	// Set the graphical style
	QApplication::setStyle(QStringLiteral("breeze"));

	// Create the world
	std::shared_ptr<World> world = std::make_shared<World>(512, 512);
	world->init();
	for (int i=2; i<world->width()-5; i+=8)
		PatternsLibrary::drawGliderAt(world, i, 2);
	world->swap();

	// Create the engine
	StandardCellRules rules;
	MapReduceEngine engine(world, rules);
	engine.setTileSize(32);

	// Create the main window & layout
	MainWindow mainWindow(world);

	QObject::connect(&mainWindow, &MainWindow::step,
					 &engine,     &Engine::run);
	QObject::connect(&engine,     &Engine::cellsChanged,
					&mainWindow,  &MainWindow::detectStop);
	QObject::connect(&engine,     &Engine::finished,
					 &mainWindow, &MainWindow::stepFinished);

	mainWindow.show();

	return app.exec();
}
