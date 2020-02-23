#include <cmath>

#include <iostream>

#include <QProcess>
#include <QThread>
#include <QAbstractEventDispatcher>


#include "mainwindow.hpp"


MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
}

void MainWindow::set_progress(float progress)
{
	MainWindow::conversion_progress = progress;
}

float MainWindow::get_progress()
{
	return this->conversion_progress;
}

void MainWindow::set_total_time(unsigned int t_time)
{
	this->media_total_time = t_time;
}

unsigned int MainWindow::get_total_time()
{
	return this->media_total_time;
}

void MainWindow::execute_on_stdout(QProcess *process)
{
	std::cout << "Output: "<< process->readAllStandardError().toStdString() << std::endl;
}

void MainWindow::conversion_done_bridge()
{
	emit conversionDone();
}

void MainWindow::handle_process_error()
{
	std::cerr << "GONK!!" << std::endl;
}

void MainWindow::read_total_time(const QString &file_path, const QString &file_directory_path)
{
	QProcess *process = new QProcess(this);
	connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handle_process_error()));
	process->setWorkingDirectory(file_directory_path);
	connect(process, &QProcess::readyReadStandardOutput, [process, this]()->void {
	    std::string ffprobe_standard_output = process->readAllStandardOutput().toStdString();
	    this->set_total_time(std::round(std::stod(ffprobe_standard_output)));
	});

	connect(process, SIGNAL(finished(int)), process, SLOT(deleteLater()));

	QString ffprobe = "ffprobe";
	QString source_file = " -i " + file_path;
	QString ffprobe_params = " -show_entries format=duration -v quiet -of csv=p=0";

	process->start(ffprobe + source_file + ffprobe_params);

	connect(this, &MainWindow::destroyed, process, &QProcess::kill);

	process->waitForFinished();
}

void MainWindow::convert_clicked(const QString &file_path)
{
	QString file_directory_path = file_path.mid(7, file_path.lastIndexOf('/') - 7);

	this->read_total_time(file_path, file_directory_path);

	QProcess *process = new QProcess(this);
	connect(process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handle_process_error(QProcess::ProcessError)));

////	process1.start("echo myPass");
	process->setWorkingDirectory(file_directory_path);
//	process->setProcessChannelMode(QProcess::ForwardedChannels); //koppel alle std output aan cout en cerr <- volgens dokumentasie
	connect(process, &QProcess::readyReadStandardError, [process, this]()->void {
	    std::string ffmpeg_standard_output = process->readAllStandardError().toStdString();
	    std::cout << "ffmpeg Standard Output: " << ffmpeg_standard_output << std::endl;
	    //this->set_progress(calculate_progress(process->readAllStandardError().toStdString()));
	    if (ffmpeg_standard_output.substr(0, 6) == "frame="){
		    this->set_progress(MainWindow::calculate_progress(ffmpeg_standard_output, this->get_total_time()));
		    emit progressUpdated();
		    this->thread()->eventDispatcher()->processEvents(QEventLoop::AllEvents);
		    std::cerr << this->get_progress() << std::endl;
	    }
	});

	connect(process, SIGNAL(finished(int)), process, SLOT(deleteLater()));
	connect(process, SIGNAL(finished(int)), this, SLOT(conversion_done_bridge()));

	QString ffmpeg = "ffmpeg";
	QString source_file = " -i " + file_path;
	QString convertion_configuration = " -vcodec dnxhd -acodec pcm_s16le -s 1920x1080 -r 30000/1001 -b:v 36M -pix_fmt yuv422p -f mov output.mov"; //TODO: Make this whole line dynamic based on user inputs



	process->start(ffmpeg + source_file + convertion_configuration);
	connect(this, &MainWindow::destroyed, process, &QProcess::kill);

	//process->waitForFinished();
}

float MainWindow::calculate_progress(std::string stdoutput_string, unsigned int media_duration)
{
	std::size_t start_index_of_time_indication = stdoutput_string.find("time=");
	if (start_index_of_time_indication != std::string::npos) {
		std::string time_progress_hours = stdoutput_string.substr(start_index_of_time_indication + 5, 2);
		std::string time_progress_minutes = stdoutput_string.substr(start_index_of_time_indication + 8, 2);
		std::string time_progress_seconds = stdoutput_string.substr(start_index_of_time_indication + 11, 2);
		short hours = std::stoi(time_progress_hours);
		short minutes = std::stoi(time_progress_minutes);
		short seconds = std::stoi(time_progress_seconds);
		unsigned int total_in_seconds = 0;

		if (hours >= 0 && minutes >= 0 && seconds >= 0) {
			//std::cerr << hours << ":" << minutes << ":" << seconds << std::endl;
			total_in_seconds = seconds + minutes * 60 + hours * 3600;
			return (float)total_in_seconds / (float)media_duration;
		}
	}

	return 0;
}

MainWindow::~MainWindow()
{

}
