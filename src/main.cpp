#include <memory>
#include <QApplication>

#include "World.hpp"
#include "PatternsLibrary.hpp"
#include "StandardEngine.hpp"

#include "MainWindow.hpp"


int main(int p_argc, char* p_argv[]) {
	QApplication app(p_argc, p_argv);

	// Create the world
	std::shared_ptr<World> world = std::make_shared<World>(1024, 1024);
	world->init();
	PatternsLibrary library;
	library.drawGliderAt(world, 2, 2);
	world->swap();

	// Create the engine
	StandardEngine engine(world);

	// Create the main window & layout
	MainWindow mainWindow(world);
	mainWindow.resize(1024, 1024);

	QObject::connect(&mainWindow, &MainWindow::next,
					 &engine,     &Engine::next);
	QObject::connect(&engine,     &StandardEngine::finished,
					 &mainWindow, &MainWindow::stepFinished);

	mainWindow.show();

	return app.exec();
}
