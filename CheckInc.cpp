#include "CheckInc.h"
#include "ui_CheckInc.h"

QString fileName;

CheckInc::CheckInc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckInc)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
    about = new aboutDialog();
}

CheckInc::~CheckInc()
{
    delete ui;
}

void CheckInc::on_openButton_clicked()
{
    connect(ui->openButton, &QAbstractButton::clicked, this, &CheckInc::open);
}

void CheckInc::open()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "");
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QFileInfo f(fileName);
        ui->lineEdit->setText(fileName);
        ui->Name->setText(f.fileName());
        ui->Size->setText(QString::number(f.size()));
        ui->Touched->setText(f.lastModified().toString("MM/dd/yyyy hh:mm:ss"));
        ui->Created->setText(f.created().toString("MM/dd/yyyy hh:mm:ss"));
        file.close();
    }
}

void CheckInc::on_startButton_clicked()
{
    connect(ui->startButton, &QAbstractButton::clicked, this, &CheckInc::check);
}

void CheckInc::check()
{
    if (fileName == "")
        QMessageBox::critical(0, tr("Error"), tr("Please, open file!"));
    else
    {
        if (!ui->bytes2Button->isChecked() && !ui->bytes4Button->isChecked())
            QMessageBox::critical(0, tr("Error"), tr("Please, choose a param!"));
        else
        {
            if (ui->bytes2Button->isChecked())
            {
                Thread2 *workerThread = new Thread2;
                connect(this, &CheckInc::setName, workerThread, &Thread2::setFile);
                connect(this, &CheckInc::setEndian, workerThread, &Thread2::setEndian);
                connect(workerThread, &Thread2::maximum, ui->progressBar, &ColoredProgressBar::setMaximum);
                connect(workerThread, &Thread2::progress, ui->progressBar, &ColoredProgressBar::setValue);
                connect(workerThread, &Thread2::sendErr, ui->progressBar, &ColoredProgressBar::setErrPos);
                connect(workerThread, &Thread2::numErr, ui->Errors, &QLabel::setText);
                connect(workerThread, &Thread2::finished, workerThread, &QObject::deleteLater);
                workerThread->start();
                emit setName(fileName);
                if (ui->bigEndianRBtn->isChecked())
                    emit setEndian(true);
                else
                    emit setEndian(false);
            }
            else
            {
                Thread4 *workerThread = new Thread4;
                connect(this, &CheckInc::setName, workerThread, &Thread4::setFile);
                connect(this, &CheckInc::setEndian, workerThread, &Thread4::setEndian);
                connect(workerThread, &Thread4::maximum, ui->progressBar, &ColoredProgressBar::setMaximum);
                connect(workerThread, &Thread4::progress, ui->progressBar, &ColoredProgressBar::setValue);
                connect(workerThread, &Thread4::sendErr, ui->progressBar, &ColoredProgressBar::setErrPos);
                connect(workerThread, &Thread4::numErr, ui->Errors, &QLabel::setText);
                connect(workerThread, &Thread4::finished, workerThread, &QObject::deleteLater);
                workerThread->start();
                emit setName(fileName);
                if (ui->bigEndianRBtn->isChecked())
                    emit setEndian(true);
                else
                    emit setEndian(false);
            }
        }
    }
}

void CheckInc::on_open_logButton_clicked()
{
    connect(ui->open_logButton, &QAbstractButton::clicked, this, &CheckInc::openLog);
}

void CheckInc::openLog()
{
    QFileInfo fin(fileName);
    QFileInfo fout("logs/log-"+fin.fileName()+"-.txt");
    QUrl url = QUrl::fromLocalFile(fout.absoluteFilePath());
    if (!QDesktopServices::openUrl(url))
        QMessageBox::critical(0, tr("Error"), tr("Could not open log-file!"));
    else
        QDesktopServices::openUrl(url);
}

void CheckInc::on_aboutButton_clicked()
{
    connect(ui->aboutButton, &QAbstractButton::clicked, about, &QDialog::show);
}
