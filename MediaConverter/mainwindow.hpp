#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QObject>
#include <QProcess>


class MainWindow : public QObject
{
	Q_OBJECT
public:
	MainWindow();
	int a;
public slots:
	void convert_clicked(const QString& file_path);
	void handle_process_error(QProcess::ProcessError error);
signals:
	void conversion_done();
};

#endif // MAINWINDOW_HPP
