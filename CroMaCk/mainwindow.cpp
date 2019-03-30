#include <iostream>

#include <QProcess>
#include <QDebug>
#include <QThread>

#include "mainwindow.hpp"


MainWindow::MainWindow()
{
}

void MainWindow::convert_clicked(const QString &file_path)
{
	QProcess *process = new QProcess(this);
	connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handle_process_error(QProcess::ProcessError)));

////	process1.start("echo myPass");
	process->setWorkingDirectory("/home/zander/MediaConverter");
//	process->setProcessChannelMode(QProcess::ForwardedChannels); //kopper alle std output aan cout en cerr <- volgens dokumentasie
	connect(process, &QProcess::readyReadStandardError, [process]()->void{
			std::cout << "Output: "<< process->readAllStandardError().toStdString() << std::endl;
		});
	connect(process, SIGNAL(finished(int)), process, SLOT(deleteLater()));

	QString ffmpeg = "ffmpeg";
	QString source_file = " -i " + file_path;
	QString convertion_configuration = " -vcodec dnxhd -acodec pcm_s16le -s 1920x1080 -r 30000/1001 -b:v 36M -pix_fmt yuv422p -f mov output.mov";

	process->start(ffmpeg + source_file + convertion_configuration);
	connect(this, &MainWindow::destroyed, process, &QProcess::kill);

	std::cout << "Waiting for process" << std::endl;
	process->waitForFinished();
	std::cout << "Done waiting" << std::endl;

	emit conversion_done();
}
