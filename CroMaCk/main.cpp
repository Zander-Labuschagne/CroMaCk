#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	MainWindow mw;

	QQmlApplicationEngine engine;
	QQuickView view(&engine, 0);

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
			 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

//	qmlRegisterType<MainWindow>("Cryogen.MainWindow", 1, 0, "MainWindow");

	QObject::connect(engine.rootObjects().at(0), SIGNAL(convert(QString)), &mw, SLOT(convert_clicked(QString)));
	QObject::connect(&mw, SIGNAL(conversion_done()),(QObject *)engine.rootObjects().at(0), SLOT(onConversionDone()));
	QObject::connect(&mw, SIGNAL(progress_updated()),(QObject *)engine.rootObjects().at(0), SIGNAL(onProgressUpdated2));


	//Use views for embedding poroperties to into UI elements
	view.rootContext()->setContextProperty("mw_controller", &mw);

	return app.exec();
}
