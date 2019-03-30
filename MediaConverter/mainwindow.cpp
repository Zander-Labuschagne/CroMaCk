#include <iostream>

#include <QProcess>
#include <QDebug>

#include "mainwindow.hpp"


MainWindow::MainWindow()
{
}

void MainWindow::handle_process_error(QProcess::ProcessError error) {
   switch(error) {
   case QProcess::FailedToStart:
    qDebug() << "Failed to start, may be due to insufficient permissions";
    break;
    case QProcess::Crashed:
    qDebug() << "Program crashed.";
    break;
    //debug each case..
   }
}

void MainWindow::convert_clicked(const QString &file_path)
{
	QProcess *process = new QProcess(this);
	connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handle_process_error(QProcess::ProcessError)));

	std::cout << "Started..." << std::endl;
////	process1.start("echo myPass");
//	QString process_execution_string = "ffmpeg -i '" + file_path + "' -vcodec dnxhd -acodec pcm_s16le -s 1920x1080 -r 30000/1001 -b:v 36M -pix_fmt yuv422p -f mov output.mov";
//	QString process_execution_string = "ffmpeg --help";
	process->setWorkingDirectory("/home/zander/MediaConverter");
//	process->setArguments(QStringList() << "-i '" + file_path + "' -vcodec dnxhd -acodec pcm_s16le -s 1920x1080 -r 30000/1001 -b:v 36M -pix_fmt yuv422p -f mov output.mov");
	process->setArguments(QStringList() << "ffmpeg");
//	std::cout << process_execution_string.toStdString() << std::endl;
//	process.start("kitty");
//	std::cout << "Done." << std::endl;;
	process->setProcessChannelMode(QProcess::ForwardedChannels);
//	process->start("ffmpeg", QIODevice::ReadWrite);
	process->start("ffmpeg -i " + file_path + " -vcodec dnxhd -acodec pcm_s16le -s 1920x1080 -r 30000/1001 -b:v 36M -pix_fmt yuv422p -f mov output.mov");
//	process->start("whoami");



//	// Wait for it to start
	if(!process->waitForStarted()) {
		emit conversion_done();
		return;
	}

	bool retval = false;
	QByteArray buffer;
//	// To be fair: you only need to wait here for a bit with shutdown,
//	// but I will still leave the rest here for a generic solution
	std::cout << "Waiting for process" << std::endl;
	while ((retval = process->waitForFinished()))
		buffer.append(process->readAll());
	std::cout << "Not waiting anymore" << std::endl << buffer.toStdString() << std::endl;

//	if (!retval) {
//		std::cerr << "Process error: " << process->errorString().toStdString();
//		emit conversion_done();
//		return;
//	}
//	delete process;
	emit conversion_done();
}
