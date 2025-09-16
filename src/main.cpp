#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>

#include "World.h"
#include "PatternsLibrary.h"


int main(int p_argc, char* p_argv[]) {
	QApplication app(p_argc, p_argv);

	// Create the world
	World world(nullptr, 1024, 1024);
	world.init();
	PatternsLibrary library;
	library.drawWalkerAt(world, 2, 2);
	world.swap();

	// Create the main window & layout
	QWidget mainWindow;
	mainWindow.setWindowTitle("Life");
	mainWindow.resize(1024, 1024);

	QHBoxLayout mainLayout;
	mainLayout.addWidget(&world);
	mainWindow.setLayout(&mainLayout);
	mainWindow.show();

	return app.exec();
}
