#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	MainWindow mw;

	QQmlApplicationEngine engine;

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
			 &app, [url](QObject *obj, const QUrl &objUrl) {
		    if (!obj && url == objUrl)
			    QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);
	engine.load(url);

	QObject::connect(engine.rootObjects().at(0), SIGNAL(convert(QString)), &mw, SLOT(convert_clicked(QString)));

	engine.rootContext()->setContextProperty("mw_controller", &mw);

	return app.exec();
}
