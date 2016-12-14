#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mIsRunning(false),
    mThreadNum(1)
{
    ui->setupUi(this);
    setFixedSize(400,300);
    ui->menuBar->hide();
    ui->mainToolBar->hide();
    mMapProcess = new QProcess();
    ui->statusBar->showMessage(tr("Ready"));
    connect(mMapProcess, SIGNAL(finished(int)), this, SLOT(map_finish()));
    mOutputName = "lq";
}

MainWindow::~MainWindow()
{
    mMapProcess->deleteLater();
    delete ui;
}

void MainWindow::on_toolButton_input_clicked()
{
     qDebug("input file\n");
     QString file_path = QFileDialog::getExistingDirectory(this,"请选择输入文件路径...","./");
     if (!file_path.isEmpty())
     {
         mInputPath = file_path;
         ui->lineEdit_input->setText(mInputPath);
         if (ui->lineEdit_output->text().isEmpty())
         {
             mOutputPath = file_path;
             ui->lineEdit_output->setText(mInputPath);
         }
     }
     qDebug("%s", qPrintable(mInputPath) );
}

void MainWindow::on_toolButton_output_clicked()
{
     qDebug("output file\n");
     QString file_path = QFileDialog::getExistingDirectory(this,"请选择输出文件路径...","./");
     if (!file_path.isEmpty())
     {
         mOutputPath = file_path;
         ui->lineEdit_output->setText(mOutputPath);
     }
      qDebug("%s", qPrintable(mOutputPath) );
}

void MainWindow::on_spinBox_thread_valueChanged(int arg1)
{
    mThreadNum = arg1;
    qDebug("thread: %d\n", mThreadNum);
}

void MainWindow::on_lineEdit_input_textEdited(const QString &arg1)
{
    mInputPath = arg1;
    qDebug("%s", qPrintable(mInputPath) );
}

void MainWindow::on_lineEdit_output_textEdited(const QString &arg1)
{
    mOutputPath = arg1;
    qDebug("%s", qPrintable(mOutputPath) );
}

void MainWindow::on_buttonBox_accepted()
{
    QStringList arg;
    if (!check_config())
        return;
    mOutputPath += "/";
    mOutputPath += mOutputName;
    mOutputPath += ".png";
    qDebug("%s", qPrintable(mInputPath));
    qDebug("%s", qPrintable(mOutputPath));
    QFileInfo * inputInfo = new QFileInfo(mInputPath);
    QFileInfo * outputInfo = new QFileInfo(mOutputPath);
    QString inputPath = inputInfo->absoluteFilePath();
    QString outputPath = outputInfo->absoluteFilePath();
    qDebug("%s", qPrintable(inputPath));
    qDebug("%s", qPrintable(outputPath));
    if (mThreadNum < 1)
        mThreadNum = 1;
    QString strthread = QString("-N%1").arg(mThreadNum);
    //arg << "D:\\projects\\mc-map\\testFile\\testWorld\\region";
    arg << inputInfo->absoluteFilePath() << outputInfo->absoluteFilePath() << "+RTS" << strthread << "-H";
    ui->statusBar->showMessage(tr("Start"));
    mStartTime = time(NULL);
    if (!mIsRunning)
    {
        mIsRunning = true;
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->toolButton_input->setEnabled(false);
        ui->toolButton_output->setEnabled(false);
        ui->lineEdit_output->setEnabled(false);
        ui->lineEdit_input->setEnabled(false);
        ui->lineEdit_output->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->spinBox_thread->setEnabled(false);
        mMapProcess->start("main", arg);
        ui->statusBar->showMessage(tr("Running..."));
    }

}

void MainWindow::map_finish()
{
    mEndTime = time(NULL);
    unsigned int time = mEndTime - mStartTime;
    QString str =QString("Finished in\t%1s").arg(time);
    mIsRunning = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    ui->toolButton_input->setEnabled(true);
    ui->toolButton_output->setEnabled(true);
    ui->lineEdit_output->setEnabled(true);
    ui->lineEdit_input->setEnabled(true);
    ui->lineEdit_output->setEnabled(true);
    ui->checkBox->setEnabled(true);
    ui->spinBox_thread->setEnabled(true);
    ui->statusBar->showMessage(str);
}

 bool MainWindow::check_config()
 {
     if (mInputPath == "")
     {
         ui->statusBar->showMessage(tr("ERROR: No Input Path"));
         return false;
     }
     else if (mOutputPath == "")
     {
         ui->statusBar->showMessage(tr("WARNING: No Output Path"));
         return false;
     }
     else if (mOutputName == "")
     {
         ui->statusBar->showMessage(tr("WARNING: No Output Name"));
         return false;
     }
     return true;
 }

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    mOutputName = arg1;
    qDebug("%s", qPrintable(mOutputName) );
}
