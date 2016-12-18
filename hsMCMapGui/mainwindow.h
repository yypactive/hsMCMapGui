#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <ctime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_toolButton_input_clicked();

    void on_toolButton_output_clicked();

    void on_spinBox_thread_valueChanged(int arg1);

    void on_lineEdit_input_textEdited(const QString &arg1);

    void on_lineEdit_output_textEdited(const QString &arg1);

    void on_buttonBox_accepted();

    void map_finish();

    bool check_config();

    void on_lineEdit_textEdited(const QString &arg1);


    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString mInputPath;
    QString mOutputPath;
    QString mOutputName;
    int mThreadNum;
    time_t mStartTime, mEndTime;
    QProcess *mMapProcess;
    bool mIsRunning;
    unsigned int mYCoordinate;
};

#endif // MAINWINDOW_H
