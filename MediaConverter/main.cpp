#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickView>
//#include <QQmlContext>
#include <iostream>

#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	MainWindow mw;

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	QObject::connect(engine.rootObjects().at(0), SIGNAL(convert(QString)), &mw, SLOT(convert_clicked(QString)));
	QObject::connect(&mw, SIGNAL(conversion_done()),(QObject *)engine.rootObjects().at(0), SLOT(onConversionDone()));

	return app.exec();
}
