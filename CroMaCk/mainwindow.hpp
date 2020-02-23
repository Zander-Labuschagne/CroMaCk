#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QObject>
#include <QProcess>


class MainWindow : public QObject
{
Q_OBJECT
    Q_PROPERTY(float progress READ get_progress NOTIFY progressUpdated) // Read only
public:
    explicit MainWindow(QObject *parent = nullptr);
    ~MainWindow();
    float get_progress();
    static float calculate_progress(std::string stdoutput_string, unsigned int media_duration);
    unsigned int get_total_time();

public slots:
    void convert_clicked(const QString& file_path);
    void execute_on_stdout(QProcess *process);
    void conversion_done_bridge();
    void handle_process_error();
signals:
    void conversionDone();
    void progressUpdated();
private:
    float conversion_progress;
    unsigned int media_total_time;
    void set_progress(float progress);
    void read_total_time(const QString &file_path, const QString &file_directory_path);
    void set_total_time(unsigned int t_time);
};

#endif // MAINWINDOW_HPP
