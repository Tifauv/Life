#include <memory>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QtQml/qqmlregistration.h>
#include <KIconTheme>
#include <KLocalizedString>
#include <KLocalizedContext>

#include "World.hpp"
#include "PatternsLibrary.hpp"
#include "MapReduceEngine.hpp"
#include "StandardCellRules.hpp"


int main(int p_argc, char* p_argv[]) {
	KIconTheme::initTheme();
	QApplication app(p_argc, p_argv);
	KLocalizedString::setApplicationDomain("life");
	QApplication::setOrganizationName(QStringLiteral("CatWitch"));
	QApplication::setOrganizationDomain(QStringLiteral("catwitch.eu"));
	QApplication::setApplicationName(QStringLiteral("Life"));
	QApplication::setDesktopFileName(QStringLiteral("eu.catwitch.life"));

	// Set the graphical style
	QApplication::setStyle(QStringLiteral("breeze"));
	if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
		QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
	}

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
	engine.loadFromModule("eu.catwitch.life.qml", "MainWindow");

	// Fail if the main window was not found
	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	// Alright, let's go !
	return app.exec();
}

#ifdef OLDCODE
void old_main(int p_argc, char* p_argv[]) {
	QApplication app(p_argc, p_argv);

	// Create the world
	std::shared_ptr<World> world = std::make_shared<World>(512, 512);
	world->init();
	for (uint i=2; i<world->width()-5; i+=8)
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
#endif
